#include "pch.h"
#include "passive_actor_sphere_shape.h"

namespace accord
{

	PassiveActorSphereShape::PassiveActorSphereShape(shape::basic::Sphere sphere)
		: Sphere(sphere), shape::basic::Sphere(sphere)
	{

	}

	bool PassiveActorSphereShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return IsWithinOrOnBorder(position);
	}

	bool PassiveActorSphereShape::IsSubvolumeInsideBorder(const shape::relation::Box& box) const
	{
		return IsEnveloping(box);
	}

	bool PassiveActorSphereShape::IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const
	{
		return IsOverlapping(box);
	}

	void PassiveActorSphereShape::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Sphere>(*this);
	}
}
