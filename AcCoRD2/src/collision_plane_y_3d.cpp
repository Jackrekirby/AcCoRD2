#include "collision_plane_y_3d.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneY3D::PlaneY3D(double y)
		: AbstractPlane3D(y, Axis3D::y)
	{

	}

	std::optional<double> PlaneY3D::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithPositiveFace(origin.y, end.y);
	}

	std::optional<double> PlaneY3D::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithNegativeFace(origin.y, end.y);
	}

	Vec3d PlaneY3D::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { Lerp(origin.x, end.x, time), GetPosition(), Lerp(origin.z, end.z, time) };
	}

	Vec3d PlaneY3D::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { end.x, MirrorPosition(end.y, intersection.y), end.z };
	}
}