#include "pch.h"
#include "zeroth_order_reaction.h"

namespace accord
{
	ZerothOrderReaction::ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, 
		const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
		: products(products), reaction_rate(reaction_rate),
		microscopic_regions(microscopic_regions), mesoscopic_regions(mesoscopic_regions)
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

	const MicroscopicRegionIDs& ZerothOrderReaction::GetMicroscopicRegions() const
	{
		return microscopic_regions;
	}

	const MesoscopicRegionIDs& ZerothOrderReaction::GetMesoscopicRegions() const
	{
		return mesoscopic_regions;
	}

}