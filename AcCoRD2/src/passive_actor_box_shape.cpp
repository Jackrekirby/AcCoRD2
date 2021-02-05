#include "pch.h"
#include "passive_actor_box_shape.h"

namespace accord
{

	PassiveActorBoxShape::PassiveActorBoxShape(shape::basic::Box box)
		: Box(box), shape::basic::Box(box)
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
}
