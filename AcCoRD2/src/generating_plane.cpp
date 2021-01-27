#include "pch.h"
#include "generating_plane.h"
#include "vec3d.h"
#include "vec2d.h"

namespace accord::shape::generating
{
	Plane::Plane(double position, const Axis3D& axis)
		: basic::Plane(position, axis)
	{

	}

	Plane::Plane(basic::Plane plane)
		: basic::Plane(plane)
	{

	}

	Vec3d Plane::PlacePointOnPlane(const Vec2d& position) const
	{
		return { GetPosition(), position, GetAxis() };
	}

	Vec3d Plane::GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const
	{
		return { GetPosition() + normal, tangential, GetAxis() };
	}

	void to_json(Json& j, const Plane& plane)
	{
		j = static_cast<basic::Plane>(plane);
	}
}