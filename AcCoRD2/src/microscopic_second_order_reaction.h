#pragma once
#include "pch.h"
// is it better to pass id's or grids? (can a grid be passed?)
#include "microscopic_region2.h"
#include "microscopic_grid2.h"

// store has reacted per normal molecule, with each subvolume storing a needs refresh (all molecules are recreated anyway)
// create has reacted list every time


namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;
	class Region2;

	class OneReactantSecondOrderReaction
	{
	public:
		OneReactantSecondOrderReaction(MoleculeID reactant, const MoleculeIDs& products);
	};

	class TwoReactantSecondOrderReaction
	{
	public:
		TwoReactantSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, 
			const MoleculeIDs& products);

		void Run()
		{

		}

		void CalculateReactions()
		{
			for (auto& subvolume_a : reactant_a_grid->GetSubvolumes())
			{
				for (auto& subvolume_b : subvolume_a.GetRelation(reactant_b).GetSubvolumes())
				{
					CompareMoleculesInSubvolumes(subvolume_a, *subvolume_b);
				}
			}
		}

		void CompareMoleculesInSubvolumes(Subvolume2& s1, Subvolume2& s2)
		{
			double time = region->GetEventTime();
			std::vector<bool> has_reacted1(s1.GetNormalMolecules().size(), false);
			std::vector<bool> has_reacted2(s2.GetNormalMolecules().size(), false);
			int n_reactions = 0;
			int i1 = 0, i2 = 0;
			for (auto& m1 : s1.GetNormalMolecules())
			{
				for (auto& m2 : s2.GetNormalMolecules())
				{
					if (has_reacted2.at(i2)) continue;
					if ((m1.GetPosition() - m2.GetPosition()).Size() < binding_radius)
					{
						for (auto& product : products)
						{
							Vec3d midpoint = m1.GetPosition() + 0.5 * (m2.GetPosition() - m1.GetPosition());
							region->AddMolecule(product, midpoint, time);
						}

						has_reacted1.at(i1) = true;
						has_reacted2.at(i2) = true;
						n_reactions++;
						break;
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
				if (has_reacted1.at(i)) ms1.emplace_back(m1);
				i++;
			}
			i = 0;
			for (auto& m2 : s2.GetNormalMolecules())
			{
				if (has_reacted2.at(i)) ms2.emplace_back(m2);
				i++;
			}
			s1.GetNormalMolecules() = ms1;
			s2.GetNormalMolecules() = ms2;
		}
	private:
		Region2* region;
		Grid2* reactant_a_grid;
		MoleculeID reactant_a;
		MoleculeID reactant_b;
		MoleculeIDs products;
		double binding_radius;
	};

	// at the moment we dont know which subvolumes are part of the region and which are not
	// you dont need to check if subvolume needs to be cleared of subvolumes in parent region
	// you dont know which molecules  need to be added to the normal list and which to the recent list
	// after all second order reactions u will hvae to go back and update lists
	// or add all products to recent list and rewrite normal list each time.
	class SecondOrderReactions
	{
	public:
		void AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products, Region2* region);

	private:
		std::vector<OneReactantSecondOrderReaction> one_reactant_reactions;
		std::vector<TwoReactantSecondOrderReaction> two_reactant_reactions;

	};
}