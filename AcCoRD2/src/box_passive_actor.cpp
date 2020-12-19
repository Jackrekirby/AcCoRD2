#include "pch.h"
#include "box_passive_actor.h"

namespace accord
{
	BoxPassiveActor::BoxPassiveActor(shape::relation::Box box, MoleculeIDs molecule_ids, double start_time,
		int priority, EventQueue* event_queue, double time_step, ActiveActorID id, bool record_positions, bool record_time)
		: PassiveActor(molecule_ids, start_time, priority, event_queue, time_step, id, record_positions,
		record_time), box(box)
	{
		AddMicroscopicSubvolumesWhichAreInsideActor(molecule_ids);
		CreateFiles();
	}

	const PassiveActorBoxShape* const BoxPassiveActor::GetShape() const
	{
		return &box;
	}
}
