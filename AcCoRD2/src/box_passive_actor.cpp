#include "pch.h"
#include "box_passive_actor.h"

namespace accord
{

	PassiveActorBoxShape::PassiveActorBoxShape(shape::basic::Box box)
		: Box(box)
	{

	}

	bool PassiveActorBoxShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return IsWithinBorder(position);
	}

	bool PassiveActorBoxShape::IsSubvolumeInsideBorder(const shape::relation::Box& box) const
	{
		return IsEnveloping(box);
	}

	bool PassiveActorBoxShape::IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const
	{
		return IsOverlapping(box);
	}

	void PassiveActorBoxShape::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Box>(*this);
	}

	BoxPassiveActor::BoxPassiveActor(shape::relation::Box box, MoleculeIDs molecule_ids, double start_time,
		int priority, double time_step, ActiveActorID id, bool record_positions, bool record_time)
		: PassiveActor(molecule_ids, start_time, priority, time_step, id, record_positions,
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
