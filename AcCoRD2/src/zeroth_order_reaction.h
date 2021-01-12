#pragma once
#include "object_ids.h"

namespace accord
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate,
			const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		const MicroRegionIDs& GetMicroRegions() const;

		const MesoRegionIDs& GetMesoRegions() const;

	private:
		MoleculeIDs products;
		double reaction_rate;
		MicroRegionIDs micro_regions;
		MesoRegionIDs meso_regions;
	};
}