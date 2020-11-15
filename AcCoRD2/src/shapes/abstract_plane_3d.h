#pragma once
#include "plane.h"

#include "math/vec3d.h"
#include "math/axis.h"

namespace accord::shapes
{
	class AbstractPlane3D : public Plane
	{
	public:
		AbstractPlane3D(double position, math::Axis3D axis);

		virtual std::optional<double> CalculateCollisionTimeWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end) const = 0;

		virtual std::optional<double> CalculateCollisionTimeWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end) const = 0;

		virtual math::Vec3d CalculateIntersection(const math::Vec3d& origin, const math::Vec3d& end, double time) const = 0;

		virtual math::Vec3d CalculateReflection(const math::Vec3d& intersection, const math::Vec3d& end) const = 0;

		const math::Axis3D& GetAxis() const;
	private:
		math::Axis3D axis;
	};

	void to_json(Json& j, const AbstractPlane3D& plane);
}