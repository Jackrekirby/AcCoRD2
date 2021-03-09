// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "zeroth_order_reaction.h"

namespace accord
{
	ZerothOrderReaction::ZerothOrderReaction(const std::vector<int>& products, double reaction_rate,
		const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
		: products(products), reaction_rate(reaction_rate),
		microscopic_regions(microscopic_regions), mesoscopic_regions(mesoscopic_regions)
	{

	}

	const std::vector<int>& ZerothOrderReaction::GetProducts() const
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