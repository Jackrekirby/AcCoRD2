#pragma once
#include "object_ids.h"

namespace accord
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions);

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		const RegionIDs& GetRegions() const;

	private:
		MoleculeIDs products;
		double reaction_rate;
		RegionIDs regions;
	};
}