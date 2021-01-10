#pragma once
#include "object_ids.h"

namespace accord
{
	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const MicroRegionIDs& regions);

		MoleculeID GetReactant() const;

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		double GetTotalRate() const;

		const MicroRegionIDs& GetRegions() const;

	private:
		MoleculeID reactant;
		MoleculeIDs products;
		double reaction_rate;
		MicroRegionIDs regions;
	};
}
