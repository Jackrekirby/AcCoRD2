#include "pch.h"
#include "microscopic_second_order_reaction.h"
#include "microscopic_region2.h"
#include "microscopic_subvolume2.h"


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
		: reactant_a(reactant_a), reactant_b(reactant_b), product_grids(GetProductGrids(products, region)),
		binding_radius(binding_radius), unbinding_radius(unbinding_radius), reactant_a_grid(&(region->GetGrid(reactant_a)))
	{
		for (auto product : product_grids)
		{
			LOG_INFO("product2 = {}", product->GetMoleculeID());
		}
	}

	void TwoReactantSecondOrderReaction::Run(double current_time)
	{
		CalculateReactions(current_time);
	}

	std::vector<Grid2*> TwoReactantSecondOrderReaction::GetProductGrids(const MoleculeIDs& products, Region2* region)
	{
		std::vector<Grid2*> product_grids;
		for (auto product : products)
		{
			LOG_INFO("product = {}", product);
			product_grids.emplace_back(&(region->GetGrid(product)));
		}
		return product_grids;
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
					if (AttemptToReactMolecules(m1, m2, current_time))
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

	bool TwoReactantSecondOrderReaction::AttemptToReactMolecules(const NormalMolecule& m1, const NormalMolecule& m2, double current_time)
	{
		if ((m1.GetPosition() - m2.GetPosition()).Size() < binding_radius)
		{
			LOG_INFO("molecules reacted");
			for (auto& product_grid : product_grids)
			{
				LOG_INFO("product3 = {}", product_grid->GetMoleculeID());
				Vec3d midpoint = m1.GetPosition() + 0.5 * (m2.GetPosition() - m1.GetPosition());
				product_grid->AddMolecule(midpoint, current_time);
			}
			return true;
		}
		return false;
	}
	
}







