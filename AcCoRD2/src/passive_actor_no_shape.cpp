#include "pch.h"
#include "passive_actor_no_shape.h"

namespace accord
{
	PassiveActorNoShape::PassiveActorNoShape()
	{

	}

	bool PassiveActorNoShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return false;
	}

	bool PassiveActorNoShape::IsSubvolumeInsideBorder(const shape::relation::Box& box) const
	{
		return false;
	}

	bool PassiveActorNoShape::IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const
	{
		return false;
	}

	void PassiveActorNoShape::ToJson(Json& j) const
	{
		j = "Shapeless";
	}
}
