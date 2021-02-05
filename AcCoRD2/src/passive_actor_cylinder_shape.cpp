#include "pch.h"
#include "passive_actor_cylinder_shape.h"

namespace accord
{

	PassiveActorCylinderShape::PassiveActorCylinderShape(shape::basic::Cylinder cylinder)
		: Cylinder(cylinder), shape::basic::Cylinder(cylinder)
	{

	}

	bool PassiveActorCylinderShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return IsWithinBorder(position);
	}

	bool PassiveActorCylinderShape::IsSubvolumeInsideBorder(const shape::relation::Box& box) const
	{
		return IsEnveloping(box);
	}

	bool PassiveActorCylinderShape::IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const
	{
		return IsOverlapping(box);
	}

	void PassiveActorCylinderShape::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Cylinder>(*this);
	}
}
