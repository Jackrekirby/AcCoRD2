#include "pch.h"
#include "microscopic_second_order_reaction.h"
#include "microscopic_region2.h"
#include "microscopic_subvolume2.h"
#include "vec3b.h"


namespace accord::microscopic
{
	void SecondOrderReactions::AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products, 
		double binding_radius, double unbinding_radius, Region2* region)
	{
		if (reactant_a == reactant_b)
		{
			one_reactant_reactions.emplace_back(reactant_a, products);
		}
		else
		{
			two_reactant_reactions.emplace_back(reactant_a, reactant_b, products, binding_radius, unbinding_radius, region);
		}
	}

	void SecondOrderReactions::Run(double current_time)
	{
		for (auto& reaction : one_reactant_reactions)
		{
			reaction.Run(current_time);
		}

		for (auto& reaction : two_reactant_reactions)
		{
			reaction.Run(current_time);
		}
	}

	OneReactantSecondOrderReaction::OneReactantSecondOrderReaction
	(MoleculeID reactant, const MoleculeIDs& products)
	{

	}

	void OneReactantSecondOrderReaction::Run(double current_time)
	{
	}

	TwoReactantSecondOrderReaction::TwoReactantSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
		const MoleculeIDs& products, double binding_radius, double unbinding_radius, Region2* region)
		: reactant_a(reactant_a), reactant_b(reactant_b), products(products),
		binding_radius(binding_radius), unbinding_radius(unbinding_radius), reactant_a_grid(&(region->GetGrid(reactant_a)))
	{
	}

	void TwoReactantSecondOrderReaction::Run(double current_time)
	{
		CalculateReactions(current_time);
	}

	void TwoReactantSecondOrderReaction::CalculateReactions(double current_time)
	{
		for (auto& subvolume_a : reactant_a_grid->GetSubvolumes())
		{
			for (auto& subvolume_b : subvolume_a.GetRelation(reactant_b).GetSubvolumes())
			{
				CompareMoleculesInSubvolumes(subvolume_a, *subvolume_b, current_time);
			}
		}
	}

	void OneReactantSecondOrderReaction::CalculateReactions(double current_time)
	{
		for (auto& subvolume_a : reactant_grid->GetSubvolumes())
		{
			for (auto& subvolume_b : subvolume_a.GetRelation(reactant).GetSubvolumes())
			{
				CompareMoleculesInSubvolumes(subvolume_a, *subvolume_b, current_time);
			}
			CompareMoleculesInSubvolumes(subvolume_a, current_time);
		}
	}

	void OneReactantSecondOrderReaction::CompareMoleculesInSubvolume(Subvolume2& s, double current_time)
	{
		std::vector<bool> has_reacted(s.GetNormalMolecules().size(), false);
		int n_reactions = 0;
		int i1 = 0, i2 = 0;
		auto& molecules = s.GetNormalMolecules();
		auto m_end = molecules.begin();
		for (auto m1 = molecules.begin(); m1 != m_end; ++m1)
		{
			if (!has_reacted.at(i1)) continue;
			for (auto m2 = m1 + 1; m2 != m_end; ++m2)
			{
				if (!has_reacted.at(i2))
				{
					if (AttemptToReactMolecules(m1, m2, s, s, current_time))
					{
						has_reacted.at(i1) = true;
						has_reacted.at(i2) = true;
						n_reactions++;
						break;
					}
				}
				i2++;
			}
			i2 = 0;
			i1++;
		}

		// keep the normal molecules per subvolume which did not react
		std::vector<NormalMolecule> nm;
		nm.reserve(s.GetNormalMolecules().size() - n_reactions);
		int i = 0;
		for (auto& m : s.GetNormalMolecules())
		{
			if (!has_reacted.at(i)) nm.emplace_back(m);
			i++;
		}
		s.GetNormalMolecules() = nm;
	}

	void TwoReactantSecondOrderReaction::CompareMoleculesInSubvolumes(Subvolume2& s1, Subvolume2& s2, double current_time)
	{
		std::vector<bool> has_reacted1(s1.GetNormalMolecules().size(), false);
		std::vector<bool> has_reacted2(s2.GetNormalMolecules().size(), false);
		int n_reactions = 0;
		int i1 = 0, i2 = 0;
		for (auto& m1 : s1.GetNormalMolecules())
		{
			for (auto& m2 : s2.GetNormalMolecules())
			{
				//LOG_INFO("comparing molecules");
				if (!has_reacted2.at(i2))
				{
					if (AttemptToReactMolecules(m1, m2, s1, s2, current_time))
					{
						has_reacted1.at(i1) = true;
						has_reacted2.at(i2) = true;
						n_reactions++;
						break;
					}
				}
				i2++;
			}
			i2 = 0;
			i1++;
		}

		// keep the normal molecules per subvolume which did not react
		std::vector<NormalMolecule> ms1, ms2;
		ms1.reserve(s1.GetNormalMolecules().size() - n_reactions);
		ms2.reserve(s2.GetNormalMolecules().size() - n_reactions);
		int i = 0;
		for (auto& m1 : s1.GetNormalMolecules())
		{
			if (!has_reacted1.at(i)) ms1.emplace_back(m1);
			i++;
		}
		i = 0;
		for (auto& m2 : s2.GetNormalMolecules())
		{
			if (!has_reacted2.at(i)) ms2.emplace_back(m2);
			i++;
		}
		s1.GetNormalMolecules() = ms1;
		s2.GetNormalMolecules() = ms2;

		
	}

	// just because 2 molecule types may be the same it does not mean they will have the same diffusion coefficient
	bool TwoReactantSecondOrderReaction::AttemptToReactMolecules(const NormalMolecule& m1, const NormalMolecule& m2,
		Subvolume2& s1, Subvolume2& s2, double current_time)
	{
		if ((m1.GetPosition() - m2.GetPosition()).Size() < binding_radius)
		{
			double d1 = s1.GetGrid().GetDiffusionCoeffient();
			double d2 = s2.GetGrid().GetDiffusionCoeffient();
			Vec3d reaction_site = m1.GetPosition() + (d1 / (d1 + d2)) * (m2.GetPosition() - m1.GetPosition());

			LOG_INFO("molecules are close enough to react,  {}, {}, {}, {}", m1.GetPosition(), m2.GetPosition(), reaction_site, (d1 / (d1 + d2)));
			// if the reaction site is directly on the border then the molecules never cross the border
			// allowing molecules to diffuse across a surface which is not none
			auto p1 = s1.GetGrid().CheckMoleculePath(m1.GetPosition(), reaction_site, 20, true);
			if (p1.has_value() && (p1.value().GetPosition() == reaction_site).All())
			{
				LOG_INFO("molecule path 1");
				auto p2 = s2.GetGrid().CheckMoleculePath(m2.GetPosition(), reaction_site, 20, true);
				if (p2.has_value() && (p2.value().GetPosition() == reaction_site).All())
				{
					LOG_INFO("molecules reacted");
					for (auto product : products)
					{
						dynamic_cast<Grid2&>(p1->GetOwner()).GetRegion().AddMolecule(product, reaction_site, current_time);
					}
					return true;
				}
			}
		}
		return false;
	}
	
}







