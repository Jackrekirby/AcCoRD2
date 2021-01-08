#include "pch.h"
#include "shapeless_passive_actor.h"

namespace accord
{
	ShapelessPassiveActor::ShapelessPassiveActor(RegionIDs region_ids, MoleculeIDs molecule_ids, double start_time, 
		int priority, double time_step, ActiveActorID id, bool record_positions, bool record_time)
		: PassiveActor(region_ids, molecule_ids, start_time, priority, time_step, id, record_positions,
		record_time)
	{

	}

	const PassiveActorShape* const ShapelessPassiveActor::GetShape() const
	{
		return nullptr;
	}
}
