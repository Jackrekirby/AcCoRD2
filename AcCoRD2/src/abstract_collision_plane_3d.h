#pragma once
#include "collision_plane_1d.h"
#include "vec3d.h"
#include "axis_3d.h"

namespace accord::shape::collision
{
	class AbstractPlane3D : public Plane1D
	{
	public:
		AbstractPlane3D(double position, Axis3D axis);

		virtual std::optional<double> CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual std::optional<double> CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual Vec3d CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const = 0;

		virtual Vec3d CalculateReflection(const Vec3d& intersection, const Vec3d& end) const = 0;
	};

	void to_json(Json& j, const AbstractPlane3D& plane);
}