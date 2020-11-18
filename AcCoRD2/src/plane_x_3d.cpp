#include "plane_x_3d.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneX_3D::PlaneX_3D(double x)
		: AbstractPlane3D(x, Axis3D::x)
	{

	}

	std::optional<double> PlaneX_3D::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithPositiveFace(origin.x, end.x);
	}

	std::optional<double> PlaneX_3D::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithNegativeFace(origin.x, end.x);
	}

	Vec3d PlaneX_3D::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { position, Lerp(origin.y, end.y, time),  Lerp(origin.z, end.z, time) };
	}

	Vec3d PlaneX_3D::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { MirrorPosition(end.x, intersection.x), end.y, end.z };
	}
}