#pragma once
#include "object_ids.h"

namespace accord
{
	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions);

		MoleculeID GetReactant() const;

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		double GetTotalRate() const;

		const RegionIDs& GetRegions() const;

	private:
		MoleculeID reactant;
		MoleculeIDs products;
		double reaction_rate;
		RegionIDs regions;
	};
}
