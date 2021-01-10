#pragma once
#include "object_ids.h"

namespace accord
{
	class SecondOrderReaction
	{
	public:
		SecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products,
			double binding_radius, double unbinding_radius, const MicroRegionIDs& regions);

		MoleculeID GetReactantA() const;

		MoleculeID GetReactantB() const;

		const MoleculeIDs& GetProducts() const;

		double GetBindingRadius() const;

		double GetUnBindingRadius() const;

		const MicroRegionIDs& GetRegions() const;

	private:
		MoleculeID reactant_a;
		MoleculeID reactant_b;
		MoleculeIDs products;
		double binding_radius;
		double unbinding_radius;
		MicroRegionIDs regions;
	};
}