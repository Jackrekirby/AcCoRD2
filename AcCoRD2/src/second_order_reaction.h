#pragma once
#include "object_ids.h"

namespace accord
{
	class SecondOrderReaction
	{
	public:
		SecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products,
			double binding_radius, double unbinding_radius, double reaction_rate, 
			const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		MoleculeID GetReactantA() const;

		MoleculeID GetReactantB() const;

		const MoleculeIDs& GetProducts() const;

		double GetBindingRadius() const;

		double GetUnBindingRadius() const;

		double GetRate() const;

		const MicroRegionIDs& GetMicroRegions() const;

		const MesoRegionIDs& GetMesoRegions() const;

	private:
		MoleculeID reactant_a;
		MoleculeID reactant_b;
		MoleculeIDs products;
		double binding_radius;
		double unbinding_radius;
		double reaction_rate;
		MicroRegionIDs micro_regions;
		MesoRegionIDs meso_regions;
	};
}