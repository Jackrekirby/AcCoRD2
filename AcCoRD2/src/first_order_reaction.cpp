#include "pch.h"
#include "first_order_reaction.h"
#include "reaction_manager.h"

namespace accord
{
	FirstOrderReaction::FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const MicroRegionIDs& regions)
		: reactant(reactant), products(products), reaction_rate(reaction_rate), regions(regions)
	{

	}

	MoleculeID FirstOrderReaction::GetReactant() const
	{
		return reactant;
	}

	const MoleculeIDs& FirstOrderReaction::GetProducts() const
	{
		return products;
	}

	double FirstOrderReaction::GetRate() const
	{
		return reaction_rate;
	}

	double FirstOrderReaction::GetTotalRate() const
	{
		return ReactionManager::GetSumOfRates(reactant);
	}

	const MicroRegionIDs& FirstOrderReaction::GetRegions() const
	{
		return regions;
	}
}