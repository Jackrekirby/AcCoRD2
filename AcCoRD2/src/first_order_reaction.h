#pragma once
#include "object_ids.h"

namespace accord
{
	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, 
			const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		MoleculeID GetReactant() const;

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		double GetTotalRate() const;

		const MicroRegionIDs& GetMicroRegions() const;

		const MesoRegionIDs& GetMesoRegions() const;

	private:
		MoleculeID reactant;
		MoleculeIDs products;
		double reaction_rate;
		MicroRegionIDs micro_regions;
		MesoRegionIDs meso_regions;
	};
}
