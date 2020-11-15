#include "plane_x_3d.h"
#include "math/vec1d.h"

namespace accord::shapes
{
	PlaneX_3D::PlaneX_3D(double x)
		: AbstractPlane3D(x, math::Axis3D::x)
	{

	}

	std::optional<double> PlaneX_3D::CalculateCollisionTimeWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithPositiveFace(origin.x, end.x);
	}

	std::optional<double> PlaneX_3D::CalculateCollisionTimeWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithNegativeFace(origin.x, end.x);
	}

	math::Vec3d PlaneX_3D::CalculateIntersection(const math::Vec3d& origin, const math::Vec3d& end, double time) const
	{
		return { position, math::Lerp(origin.y, end.y, time),  math::Lerp(origin.z, end.z, time) };
	}

	math::Vec3d PlaneX_3D::CalculateReflection(const math::Vec3d& intersection, const math::Vec3d& end) const
	{
		return { math::MirrorPosition(end.x, intersection.x), end.y, end.z };
	}
}