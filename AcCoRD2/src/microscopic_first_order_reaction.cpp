#include "pch.h"
#include "microscopic_first_order_reaction.h"
#include "microscopic_region.h"
#include "microscopic_grid.h"

namespace accord::microscopic
{
	FirstOrderReaction::FirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate, double total_reaction_rate, Region* region)
		: region(region), reaction_probability(CalculateReactionProbability(reaction_rate, total_reaction_rate, region->GetTimeStep())),
		min_reaction_time(CalculateMinimumReactionTime(total_reaction_rate, region->GetTimeStep())), total_reaction_rate(total_reaction_rate),
		reaction_grid(&(region->GetGrid(reactant))), products(products)
	{
	}

	void FirstOrderReaction::Run()
	{
		std::vector<microscopic::NormalMolecule> non_reacted_molecules;
		for (auto& subvolume : reaction_grid->GetSubvolumes())
		{
			for (auto& molecule : subvolume.GetNormalMolecules())
			{
				if (Random::GenerateRealUniform() < reaction_probability)
				{
					CreateProductMolecules(molecule.GetPosition(), CalculateReactionTime());
				}
				else
				{
					non_reacted_molecules.emplace_back(molecule);
				}
			}
			subvolume.GetNormalMolecules() = non_reacted_molecules;
			non_reacted_molecules.clear();
		}
	}

	double FirstOrderReaction::CalculateMinimumReactionTime(double total_reaction_rate, double region_time_step)
	{
		return std::exp(-region_time_step * total_reaction_rate);
	}

	double FirstOrderReaction::CalculateReactionTime()
	{
		return (
			region->GetLocalTime() +
			(-std::log(Random::GenerateRealUniform(min_reaction_time, 1)) / total_reaction_rate)
		);
	}

	void FirstOrderReaction::CreateProductMolecules(const Vec3d& position, double reaction_time)
	{
		size_t molecule_type = 0;
		for (auto& grid : region->GetGrids())
		{
			int n_molecules_to_release = products.at(molecule_type);
			for (int i = 0; i < n_molecules_to_release; i++)
			{
				grid.AddMolecule(position, reaction_time);
			}
			molecule_type++;
		}
	}

	double FirstOrderReaction::CalculateReactionProbability(double reaction_rate, double total_reaction_rate, double region_time_step)
	{
		return ((reaction_rate / total_reaction_rate) * (1 - std::exp(-region_time_step * total_reaction_rate)));
	}
}