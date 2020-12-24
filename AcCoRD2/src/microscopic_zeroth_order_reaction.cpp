#include "pch.h"
#include "microscopic_zeroth_order_reaction.h"
#include "microscopic_region2.h"
#include "microscopic_grid2.h"

namespace accord::microscopic
{
	ZerothOrderReaction::ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, Region* region)
		: region(region), reaction_coefficient(CalculateReactionCoefficient(reaction_rate)),
		time(CalculateStartTime()), product_grids(GetProductGrids(products))
	{

	}

	void ZerothOrderReaction::NextRealisation()
	{
		time = CalculateStartTime();
	}

	void ZerothOrderReaction::Run()
	{
		while (time < region->GetEventTime())
		{
			//LOG_ERROR("Time = {}", time);
			CreateProductMolecules();
			time += GenerateNextReactionTime();
		}
	}

	void ZerothOrderReaction::CreateProductMolecules()
	{
		for (auto& grid : product_grids)
		{
			grid->AddMolecule(time);
		}
	}

	double ZerothOrderReaction::GenerateNextReactionTime()
	{
		return (reaction_coefficient * log(Random::GenerateRealUniform()));
	}

	double ZerothOrderReaction::CalculateStartTime()
	{
		return region->GetStartTime() + GenerateNextReactionTime();
	}

	double ZerothOrderReaction::CalculateReactionCoefficient(double reaction_rate)
	{
		return (-1 / (reaction_rate * region->GetShape().GetBasicShape().CalculateVolume()));
	}

	std::vector<Grid*> ZerothOrderReaction::GetProductGrids(const MoleculeIDs& products)
	{
		std::vector<Grid*> product_grids;
		for (auto product : products)
		{
			product_grids.emplace_back(&(region->GetGrid(product)));
		}
		return product_grids;
	}
}