#include "pch.h"
#include "shapeless_passive_actor.h"

namespace accord
{
	ShapelessPassiveActor::ShapelessPassiveActor(const MicroscopicRegionIDs& microscopic_region_ids, const MesoscopicRegionIDs& mesoscopic_region_ids, const MoleculeIDs& molecule_ids, double start_time, int priority, double time_step, const PassiveActorID& id, bool record_positions, bool record_time)
		: PassiveActor(microscopic_region_ids, mesoscopic_region_ids, molecule_ids, start_time, priority, time_step, id, record_positions,
		record_time)
	{

	}

	const PassiveActorShape* const ShapelessPassiveActor::GetShape() const
	{
		return nullptr;
	}
}
