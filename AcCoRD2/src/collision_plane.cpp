#include "pch.h"
#include "collision_plane.h"
#include "vec1d.h"
#include "vec3d.h"
#include "axis_3d.h"

namespace accord::shape::collision
{
	Plane::Plane(double position, const Axis3D& axis)
		: basic::Plane(position, axis)
	{

	}

	Plane::Plane(basic::Plane plane)
		: basic::Plane(plane)
	{

	}

	std::optional<double> Plane::CalculateCollisionTimeWithPositiveFace(double origin, double end) const
	{
		if (origin >= GetPosition() && end < GetPosition())
		{
			return (GetPosition() - origin) / (end - origin);
		}
		else
		{
			return std::nullopt;
		}
	}

	std::optional<double> Plane::CalculateCollisionTimeWithNegativeFace(double origin, double end) const
	{
		if (origin <= GetPosition() && end > GetPosition())
		{
			return (GetPosition() - origin) / (end - origin);
		}
		else
		{
			return std::nullopt;
		}
	}

	std::optional<double> Plane::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		return CalculateCollisionTimeWithPositiveFace(origin.GetAxis(GetAxis()), end.GetAxis(GetAxis()));
	}

	std::optional<double> Plane::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return CalculateCollisionTimeWithNegativeFace(origin.GetAxis(GetAxis()), end.GetAxis(GetAxis()));
	}

	Vec3d Plane::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { GetPosition(), Vec2d::Lerp(origin.GetPlane(GetAxis()), 
			end.GetPlane(GetAxis()), time), GetAxis() };
	}

	Vec3d Plane::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { Vec1d::MirrorPosition(end.GetAxis(GetAxis()), intersection.GetAxis(GetAxis())), 
			end.GetPlane(GetAxis()), GetAxis()};
	}

	void to_json(Json& j, const Plane& plane)
	{
		j = static_cast<basic::Plane>(plane);
	}
}