#pragma once
#include "molecule_id.h"
#include "microscopic_region_id.h"
#include "mesoscopic_region_id.h"

namespace accord
{
	class SecondOrderReaction
	{
	public:
		SecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b, const std::vector<int>& products,
			double binding_radius, double unbinding_radius, double reaction_rate, 
			const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions);

		const MoleculeID& GetReactantA() const;

		const MoleculeID& GetReactantB() const;

		const std::vector<int>& GetProducts() const;

		double GetBindingRadius() const;

		double GetUnBindingRadius() const;

		double GetRate() const;

		const MicroscopicRegionIDs& GetMicroscopicRegions() const;

		const MesoscopicRegionIDs& GetMesoscopicRegions() const;

	private:
		MoleculeID reactant_a;
		MoleculeID reactant_b;
		std::vector<int> products;
		double binding_radius;
		double unbinding_radius;
		double reaction_rate;
		MicroscopicRegionIDs microscopic_regions;
		MesoscopicRegionIDs mesoscopic_regions;
	};
}