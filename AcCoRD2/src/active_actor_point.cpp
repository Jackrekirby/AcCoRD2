#include "pch.h"
#include "active_actor_point.h"
#include "relation_shape_3d.h"

namespace accord
{
	ActiveActorPoint::ActiveActorPoint(const Vec3d& origin)
		: origin(origin)
	{
	}

	Vec3d ActiveActorPoint::GenerateMolecule()
	{
		return origin;
	}

	double ActiveActorPoint::CalculateVolume()
	{
		return 1.0;
	}

	bool ActiveActorPoint::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return other.IsWithinOrOnBorder(origin);
	}

	void ActiveActorPoint::ToJson(Json& j) const
	{
		j["type"] = "point";
		j["origin"] = origin;
	}
}