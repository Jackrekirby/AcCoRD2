#include "collision_plane_x_3d.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneX3D::PlaneX3D(double x)
		: AbstractPlane3D(x, Axis3D::x)
	{

	}

	std::optional<double> PlaneX3D::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithPositiveFace(origin.x, end.x);
	}

	std::optional<double> PlaneX3D::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithNegativeFace(origin.x, end.x);
	}

	Vec3d PlaneX3D::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { GetPosition(), Lerp(origin.y, end.y, time),  Lerp(origin.z, end.z, time) };
	}

	Vec3d PlaneX3D::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { MirrorPosition(end.x, intersection.x), end.y, end.z };
	}
}