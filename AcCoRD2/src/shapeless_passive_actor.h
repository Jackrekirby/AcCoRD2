#pragma once
#include "passive_actor_no_shape.h"
#include "passive_actor.h"

namespace accord
{
	class ShapelessPassiveActor : public PassiveActor
	{
	public:
		ShapelessPassiveActor(const MicroscopicRegionIDs& microscopic_region_ids, const MesoscopicRegionIDs& mesoscopic_region_ids, const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time);

		const PassiveActorShape& GetShape() const;
	private:
		PassiveActorNoShape shapeless;
	};
}