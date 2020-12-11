#pragma once
#include "pch.h"
#include "basic_plane.h"
#include "vec3d.h"

namespace accord::shape::collision
{
	class Plane : public basic::Plane
	{
	public:
		Plane(double position, const Axis3D& axis);

		std::optional<double> CalculateCollisionTimeWithPositiveFace
			(double origin, double end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace
			(double origin, double end) const;

		std::optional<double> CalculateCollisionTimeWithPositiveFace
			(const Vec3d& origin, const Vec3d& end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace
			(const Vec3d& origin, const Vec3d& end) const;

		Vec3d CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const;

		Vec3d CalculateReflection(const Vec3d& intersection, const Vec3d& end) const;
	};

	void to_json(Json& j, const Plane& plane);
}
