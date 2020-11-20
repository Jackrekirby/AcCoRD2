#pragma once
#include "collision_plane_1d.h"
#include "basic_plane.h"
#include "vec3d.h"
#include "axis_3d.h"

namespace accord::shape::collision
{
	class AbstractPlane : public basic::AbstractPlane, public Plane1D
	{
	public:
		AbstractPlane(double position, Axis3D axis);

		virtual std::optional<double> CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual std::optional<double> CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual Vec3d CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const = 0;

		virtual Vec3d CalculateReflection(const Vec3d& intersection, const Vec3d& end) const = 0;

		const double& GetPosition() const;
	};

	void to_json(Json& j, const AbstractPlane& plane);
}