// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_second_order_reaction.h"
#include "microscopic_region.h"
#include "microscopic_subvolume.h"
#include "vec3b.h"

namespace accord::microscopic
{
	TwoReactantSecondOrderReaction::TwoReactantSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b,
		const std::vector<int>& products, double binding_radius, double unbinding_radius, Region* region)
		: reactant_a(reactant_a), reactant_b(reactant_b), SecondOrderReaction(products, binding_radius, unbinding_radius), 
		reactant_a_grid(&(region->GetGrid(reactant_a)))
	{
		//LOG_INFO("binding radius = {}, {}", binding_radius, unbinding_radius);
	}

	void TwoReactantSecondOrderReaction::CalculateReactions(double current_time)
	{
		for (auto& subvolume_a : reactant_a_grid->GetSubvolumes())
		{
			bool& is_reacting = subvolume_a.GetIsReacting();
			if (!is_reacting)
			{
				is_reacting = true;
				auto& normal_molecules = subvolume_a.GetNormalMolecules();
				subvolume_a.GetHasReacted().assign(normal_molecules.size(), false);
				subvolume_a.GetNonReactedNormalMolecules() = normal_molecules;
				normal_molecules.clear();
			}
			for (auto& subvolume_b : subvolume_a.GetRelation(reactant_b).GetSubvolumes())
			{
				bool& is_reacting2 = subvolume_b->GetIsReacting();
				if (!is_reacting2)
				{
					is_reacting2 = true;
					auto& normal_molecules2 = subvolume_b->GetNormalMolecules();
					subvolume_b->GetHasReacted().assign(normal_molecules2.size(), false);
					subvolume_b->GetNonReactedNormalMolecules() = normal_molecules2;
					normal_molecules2.clear();
				}
			}
		}

		for (auto& subvolume_a : reactant_a_grid->GetSubvolumes())
		{
			//LOG_INFO("SubvolumeA id = {}, molecule id = {}, num_molecules = {}", subvolume_a.GetSubvolumeID(), subvolume_a.GetMoleculeID(), subvolume_a.GetNormalMolecules().size());
			for (auto& subvolume_b : subvolume_a.GetRelation(reactant_b).GetSubvolumes())
			{
				//LOG_INFO("SubvolumeB id = {}, molecule id = {}, num_molecules = {}", subvolume_b->GetSubvolumeID(), subvolume_b->GetMoleculeID(), subvolume_b->GetNormalMolecules().size());
				CompareMoleculesInSubvolumes(subvolume_a, *subvolume_b, current_time);
			}
		}

		for (auto& subvolume_a : reactant_a_grid->GetSubvolumes())
		{
			bool& is_reacting = subvolume_a.GetIsReacting();
			if (is_reacting)
			{
				is_reacting = false;
				auto& ms1 = subvolume_a.GetNormalMolecules();
				auto& has_reacted1 = subvolume_a.GetHasReacted();
				int i = 0;
				for (auto& m1 : subvolume_a.GetNonReactedNormalMolecules())
				{
					if (!has_reacted1.at(i)) ms1.emplace_back(m1);
					i++;
				}
				i = 0;
			}
			for (auto& subvolume_b : subvolume_a.GetRelation(reactant_b).GetSubvolumes())
			{
				bool& is_reacting2 = subvolume_b->GetIsReacting();
				if (is_reacting2)
				{
					is_reacting2 = false;
					auto& ms2 = subvolume_b->GetNormalMolecules();
					auto& has_reacted2 = subvolume_b->GetHasReacted();
					int i = 0;
					for (auto& m2 : subvolume_b->GetNonReactedNormalMolecules())
					{
						if (!has_reacted2.at(i)) ms2.emplace_back(m2);
						i++;
					}
					i = 0;
				}
			}
		}
	}


	OneReactantSecondOrderReaction::OneReactantSecondOrderReaction(const MoleculeID& reactant,
		const std::vector<int>& products, double binding_radius, double unbinding_radius, Region* region)
		: reactant(reactant), SecondOrderReaction(products, binding_radius, unbinding_radius),
		reactant_grid(&(region->GetGrid(reactant)))
	{

	}

	void OneReactantSecondOrderReaction::CalculateReactions(double current_time)
	{
		for (auto& subvolume_a : reactant_grid->GetSubvolumes())
		{
			for (auto& subvolume_b : subvolume_a.GetRelation(reactant).GetSubvolumes())
			{
				CompareMoleculesInSubvolumes(subvolume_a, *subvolume_b, current_time);
			}
			CompareMoleculesInSubvolume(subvolume_a, current_time);
		}
	}

	void OneReactantSecondOrderReaction::CompareMoleculesInSubvolume(Subvolume& s, double current_time)
	{
		//LOG_INFO("CompareMoleculesInSubvolume");
		std::vector<bool> has_reacted(s.GetNormalMolecules().size(), false);
		int n_reactions = 0;
		int i1 = 0, i2 = 0;
		auto& molecules = s.GetNormalMolecules();
		auto m_end = molecules.end();
		for (auto m1 = molecules.begin(); m1 != m_end; ++m1)
		{
			if (has_reacted.at(i1)) continue;
			i2 = i1 + 1;
			for (auto m2 = m1 + 1; m2 != m_end; ++m2)
			{
				//LOG_INFO("checking molecule in molecule");
				if (!has_reacted.at(i2))
				{
					if (AttemptToReactMolecules(*m1, *m2, s, s, current_time))
					{
						//LOG_INFO("molecule reacted in same subvolume {} {}", i1, i2);
						has_reacted.at(i1) = true;
						has_reacted.at(i2) = true;
						n_reactions++;
						break;
					}
				}
				i2++;
			}
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


	SecondOrderReaction::SecondOrderReaction(const std::vector<int>& products, double binding_radius, double unbinding_radius)
		: products(products), binding_radius(binding_radius), unbinding_radius(unbinding_radius), n_products(CalculateNumberOfProductMolecules(products))
	{
		if (n_products <= 2)
		{
			AssignProductsAB();
		}
	}

	void SecondOrderReaction::CompareMoleculesInSubvolumes(Subvolume& s1, Subvolume& s2, double current_time)
	{
		//LOG_INFO("Compare Molecules");
		auto& has_reacted1 = s1.GetHasReacted();
		auto& has_reacted2 = s2.GetHasReacted();
		//has_reacted1.resize(s1.GetNormalMolecules().size());
		//has_reacted2.resize(s2.GetNormalMolecules().size());

		//for (auto&& r : has_reacted1)
		//{
		//	r = false;
		//}

		//for (auto&& r : has_reacted2)
		//{
		//	r = false;
		//}
		//if (&s1 == &s2) LOG_INFO("SAME SUBVOLUMES");
		//std::vector<bool> has_reacted1(s1.GetNormalMolecules().size(), false);
		//std::vector<bool> has_reacted2(s2.GetNormalMolecules().size(), false);
		size_t i1 = 0, i2 = 0;
		for (auto& m1 : s1.GetNonReactedNormalMolecules())
		{
			if (!has_reacted1.at(i1))
			{
				for (auto& m2 : s2.GetNonReactedNormalMolecules())
				{
					//LOG_INFO("checking molecules");
					//LOG_INFO("comparing molecules");
					if (!has_reacted2.at(i2))
					{
						if (AttemptToReactMolecules(m1, m2, s1, s2, current_time))
						{
							//LOG_INFO("molecule reacted in different subvolume");
							has_reacted1.at(i1) = true;
							has_reacted2.at(i2) = true;
							break;
						}
					}
					i2++;
				}
				i2 = 0;
			}
			i1++;
		}

		//// keep the normal molecules per subvolume which did not react
		//auto& ms1 = s1.GetNonReactedNormalMolecules();
		//auto& ms2 = s2.GetNonReactedNormalMolecules();
		//ms1.clear();
		//ms2.clear();
		////ms1.reserve(s1.GetNormalMolecules().size() - n_reactions);
		////ms2.reserve(s2.GetNormalMolecules().size() - n_reactions);
		//int i = 0;
		//for (auto& m1 : s1.GetNormalMolecules())
		//{
		//	if (!has_reacted1.at(i)) ms1.emplace_back(m1);
		//	i++;
		//}
		//i = 0;
		//for (auto& m2 : s2.GetNormalMolecules())
		//{
		//	if (!has_reacted2.at(i)) ms2.emplace_back(m2);
		//	i++;
		//}
		//s1.GetNormalMolecules() = ms1;
		//s2.GetNormalMolecules() = ms2;

		
	}

	// just because 2 molecule types may be the same it does not mean they will have the same diffusion coefficient
	bool SecondOrderReaction::AttemptToReactMolecules(const NormalMolecule& m1, const NormalMolecule& m2,
		Subvolume& s1, Subvolume& s2, double current_time)
	{
		if ((m1.GetPosition() - m2.GetPosition()).Size() < binding_radius)
		{
			double d1 = s1.GetGrid().GetDiffusionCoeffient();
			double d2 = s2.GetGrid().GetDiffusionCoeffient();
			double diffusion_coefficient = (d1 / (d1 + d2));
			Vec3d reaction_site = m1.GetPosition() + diffusion_coefficient * (m2.GetPosition() - m1.GetPosition());

			//LOG_INFO("molecules are close enough to react,  {}, {}, {}, {}", m1.GetPosition(), m2.GetPosition(), reaction_site, (d1 / (d1 + d2)));
			// if the reaction site is directly on the border then the molecules never cross the border
			// allowing molecules to diffuse across a surface which is not none
			auto p1 = s1.GetGrid().CheckMoleculePath(m1.GetPosition(), reaction_site, 20, true);
			if (p1.has_value() && (p1.value().GetPosition() == reaction_site).All())
			{
				//LOG_INFO("molecule path 1");
				auto p2 = s2.GetGrid().CheckMoleculePath(m2.GetPosition(), reaction_site, 20, true);
				if (p2.has_value() && (p2.value().GetPosition() == reaction_site).All())
				{
					Region& reaction_region = dynamic_cast<Grid&>(p1->GetOwner()).GetRegion();
					//LOG_INFO("molecules reacted {}", n_products);
					if (n_products == 1)
					{
						reaction_region.AddMolecule(product_a, reaction_site, current_time);
					}
					else if(n_products == 2)
					{
						
						double relative_unbinding_radius = unbinding_radius * diffusion_coefficient;
						Vec3d offset = (m1.GetPosition() - reaction_site).Normalise() * relative_unbinding_radius;
						Vec3d product_a_site = reaction_site + offset;
						Vec3d product_b_site = reaction_site - offset;
						auto product_a_destination = reaction_region.GetGrid(product_a).CheckMoleculePath(reaction_site, product_a_site, 20);
						if (product_a_destination.has_value())
						{
							product_a_destination->GetOwner().AddMolecule(product_a_destination->GetPosition(), current_time);
						}
						auto product_b_destination = reaction_region.GetGrid(product_b).CheckMoleculePath(reaction_site, product_b_site, 20);
						if (product_b_destination.has_value())
						{
							product_b_destination->GetOwner().AddMolecule(product_b_destination->GetPosition(), current_time);
						}
					}
					else if (n_products > 2)
					{

						size_t molecule_type = 0;
						double relative_unbinding_radius = unbinding_radius * diffusion_coefficient;
						for (auto& grid : reaction_region.GetGrids())
						{
							int n_molecules_to_release = products.at(molecule_type);
							for (int i = 0; i < n_molecules_to_release; i++)
							{
								Vec3d product_site = reaction_site + relative_unbinding_radius * Vec3d::GenerateRandomPolar();

								auto product_destination = grid.CheckMoleculePath(reaction_site, product_site, 20);
								if (product_destination.has_value())
								{
									product_destination->GetOwner().AddMolecule(product_destination->GetPosition(), current_time);
								}
							}
							molecule_type++;
						}
					}
					return true;
				}
			}
		}
		return false;
	}

	int SecondOrderReaction::CalculateNumberOfProductMolecules(const std::vector<int>& products)
	{
		int count = 0;
		for (auto& product : products)
		{
			count += product;
		}
		return count;
	}

	void SecondOrderReaction::AssignProductsAB()
	{
		int count = 0;
		int molecule_type = 0;
		for (int product : products)
		{
			//LOG_INFO("Number of product type {} = {}", molecule_type, product);
			if (product > 0)
			{
				if (count == 0)
				{
					if (product == 1)
					{
						product_a = molecule_type;
					}
					else // (product == 2)
					{
						product_a = molecule_type;
						product_b = molecule_type;
					}
				}
				else // (count == 1)
				{
					product_b = molecule_type;
				}
			}
			count += product;
			molecule_type++;
			if (count >= 2) break;
		}
		//LOG_INFO("Product A = {}, Product B = {}", product_a, product_b);
	}
	
}







