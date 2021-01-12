#include "pch.h"
#include "zeroth_order_reaction.h"

namespace accord
{
	ZerothOrderReaction::ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, 
		const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions)
		: products(products), reaction_rate(reaction_rate), 
		micro_regions(micro_regions), meso_regions(meso_regions)
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

	const MicroRegionIDs& ZerothOrderReaction::GetMicroRegions() const
	{
		return micro_regions;
	}

	const MesoRegionIDs& ZerothOrderReaction::GetMesoRegions() const
	{
		return meso_regions;
	}

}