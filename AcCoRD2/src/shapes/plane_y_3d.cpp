#include "plane_y_3d.h"
#include "math/vec1d.h"

namespace accord::shapes
{
	PlaneY_3D::PlaneY_3D(double y)
		: AbstractPlane3D(y, math::Axis3D::y)
	{

	}

	std::optional<double> PlaneY_3D::CalculateCollisionTimeWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithPositiveFace(origin.y, end.y);
	}

	std::optional<double> PlaneY_3D::CalculateCollisionTimeWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithNegativeFace(origin.y, end.y);
	}

	math::Vec3d PlaneY_3D::CalculateIntersection(const math::Vec3d& origin, const math::Vec3d& end, double time) const
	{
		return { math::Lerp(origin.x, end.x, time), position, math::Lerp(origin.z, end.z, time) };
	}

	math::Vec3d PlaneY_3D::CalculateReflection(const math::Vec3d& intersection, const math::Vec3d& end) const
	{
		return { end.x, math::MirrorPosition(end.y, intersection.y), end.z };
	}
}