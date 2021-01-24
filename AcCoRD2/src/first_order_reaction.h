#pragma once
#include "molecule_id.h"
#include "microscopic_region_id.h"
#include "mesoscopic_region_id.h"

namespace accord
{
	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate,
			const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions);

		const MoleculeID& GetReactant() const;

		const std::vector<int>& GetProducts() const;

		double GetRate() const;

		double GetTotalRate() const;

		const MicroscopicRegionIDs& GetMicroscopicRegions() const;

		const MesoscopicRegionIDs& GetMesoscopicRegions() const;

	private:
		MoleculeID reactant;
		std::vector<int> products;
		double reaction_rate;
		MicroscopicRegionIDs microscopic_regions;
		MesoscopicRegionIDs mesoscopic_regions;
	};
}
