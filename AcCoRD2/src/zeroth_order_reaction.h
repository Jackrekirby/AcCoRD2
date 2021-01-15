#pragma once
#include "molecule_id.h"
#include "microscopic_region_id.h"
#include "mesoscopic_region_id.h"

namespace accord
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate,
			const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions);

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		const MicroscopicRegionIDs& GetMicroscopicRegions() const;

		const MesoscopicRegionIDs& GetMesoscopicRegions() const;

	private:
		MoleculeIDs products;
		double reaction_rate;
		MicroscopicRegionIDs microscopic_regions;
		MesoscopicRegionIDs mesoscopic_regions;
	};
}