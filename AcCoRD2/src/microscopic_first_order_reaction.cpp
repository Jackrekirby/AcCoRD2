#include "pch.h"
#include "microscopic_first_order_reaction.h"
#include "microscopic_region2.h"
#include "microscopic_grid2.h"

namespace accord::microscopic
{
	FirstOrderReaction::FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, double total_reaction_rate, Region2* region)
		: region(region), reaction_probability(CalculateReactionProbability(reaction_rate, total_reaction_rate, region->GetTimeStep())),
		min_reaction_time(CalculateMinimumReactionTime(total_reaction_rate, region->GetTimeStep())),
		product_grids(GetProductGrids(products)), reaction_grid(&(region->GetGrid(reactant)))
	{
		LOG_INFO("reaction probability = {}", reaction_probability);
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
		LOG_INFO("local time = {}, min_reaction_time = {}", region->GetLocalTime(), min_reaction_time);
		return (region->GetLocalTime() + Random::GenerateRealUniform(min_reaction_time, 1));
	}

	void FirstOrderReaction::CreateProductMolecules(const Vec3d& position, double reaction_time)
	{
		for (auto& grid : product_grids)
		{
			grid->AddMolecule(position, reaction_time);
		}
	}

	double FirstOrderReaction::CalculateReactionProbability(double reaction_rate, double total_reaction_rate, double region_time_step)
	{
		return ((reaction_rate / total_reaction_rate) * (1 - std::exp(-region_time_step * total_reaction_rate)));
	}

	std::vector<Grid2*> FirstOrderReaction::GetProductGrids(const MoleculeIDs& products)
	{
		std::vector<Grid2*> product_grids;
		for (auto product : products)
		{
			product_grids.emplace_back(&(region->GetGrid(product)));
		}
		return product_grids;
	}
}