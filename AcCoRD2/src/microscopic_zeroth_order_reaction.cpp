#include "pch.h"
#include "microscopic_zeroth_order_reaction.h"
#include "microscopic_region.h"
#include "microscopic_grid.h"

namespace accord::microscopic
{
	ZerothOrderReaction::ZerothOrderReaction(const std::vector<int>& products, double reaction_rate, Region* region)
		: region(region), reaction_coefficient(CalculateReactionCoefficient(reaction_rate)),
		time(GenerateNextReactionTime()), products(products)
	{

	}

	void ZerothOrderReaction::NextRealisation()
	{
		time = GenerateNextReactionTime();
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
		size_t molecule_type = 0;
		for (auto& grid : region->GetGrids())
		{
			int n_molecules_to_release = products.at(molecule_type);
			for (int i = 0; i < n_molecules_to_release; i++)
			{
				//LOG_INFO("Creating Zeroth products {}", molecule_type);
				grid.AddMolecule(time);
			}
			molecule_type++;
		}
	}

	double ZerothOrderReaction::GenerateNextReactionTime()
	{
		return (reaction_coefficient * log(Random::GenerateRealUniform()));
	}

	double ZerothOrderReaction::CalculateReactionCoefficient(double reaction_rate)
	{
		return (-1 / (reaction_rate * region->GetShape().GetBasicShape().CalculateVolume()));
	}
}