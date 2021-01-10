#include "pch.h"
#include "zeroth_order_reaction.h"

namespace accord
{
	ZerothOrderReaction::ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, const MicroRegionIDs& regions)
		: products(products), reaction_rate(reaction_rate), regions(regions)
	{

	}

	const MoleculeIDs& ZerothOrderReaction::GetProducts() const
	{
		return products;
	}

	double ZerothOrderReaction::GetRate() const
	{
		return reaction_rate;
	}

	const MicroRegionIDs& ZerothOrderReaction::GetRegions() const
	{
		return regions;
	}
}