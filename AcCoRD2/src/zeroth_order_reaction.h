// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "molecule_id.h"
#include "microscopic_region_id.h"
#include "mesoscopic_region_id.h"

namespace accord
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const std::vector<int>& products, double reaction_rate,
			const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions);

		const std::vector<int>& GetProducts() const;

		double GetRate() const;

		const MicroscopicRegionIDs& GetMicroscopicRegions() const;

		const MesoscopicRegionIDs& GetMesoscopicRegions() const;

	private:
		std::vector<int> products;
		double reaction_rate;
		MicroscopicRegionIDs microscopic_regions;
		MesoscopicRegionIDs mesoscopic_regions;
	};
}