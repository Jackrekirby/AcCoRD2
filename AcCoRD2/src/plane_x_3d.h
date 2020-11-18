#pragma once
#include "abstract_plane_3d.h"

namespace accord::shape::collision
{
	class PlaneX_3D : public AbstractPlane3D
	{
	public:
		PlaneX_3D(double x);

		std::optional<double> CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		Vec3d CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const;

		Vec3d CalculateReflection(const Vec3d& intersection, const Vec3d& end) const;
	};
}
