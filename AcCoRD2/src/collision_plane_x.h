#pragma once
#include "abstract_collision_plane.h"

namespace accord::shape::collision
{
	class PlaneX : public Plane
	{
	public:
		PlaneX(double x);

		std::optional<double> CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		Vec3d CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const;

		Vec3d CalculateReflection(const Vec3d& intersection, const Vec3d& end) const;
	};
}
