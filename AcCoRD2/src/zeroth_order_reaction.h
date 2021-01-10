#pragma once
#include "object_ids.h"

namespace accord
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, const MicroRegionIDs& regions);

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		const MicroRegionIDs& GetRegions() const;

	private:
		MoleculeIDs products;
		double reaction_rate;
		MicroRegionIDs regions;
	};
}