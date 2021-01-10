#pragma once
#include "passive_actor.h"

namespace accord
{
	class ShapelessPassiveActor : public PassiveActor
	{
	public:
		ShapelessPassiveActor(MicroRegionIDs region_ids, MesoRegionIDs meso_region_ids, MoleculeIDs molecule_ids,
			double start_time, int priority, double time_step,
			ActiveActorID id, bool record_positions, bool record_time);

		const PassiveActorShape* const GetShape() const;
	};
}