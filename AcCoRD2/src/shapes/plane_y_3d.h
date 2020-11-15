#pragma once
#include "abstract_plane_3d.h"

namespace accord::shapes
{
	class PlaneY_3D : public AbstractPlane3D
	{
	public:
		PlaneY_3D(double y);

		std::optional<double> CalculateCollisionTimeWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end) const;

		std::optional<double> CalculateCollisionTimeWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end) const;

		math::Vec3d CalculateIntersection(const math::Vec3d& origin, const math::Vec3d& end, double time) const;

		math::Vec3d CalculateReflection(const math::Vec3d& intersection, const math::Vec3d& end) const;

	};
}
