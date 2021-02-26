#include "collision_plane_y.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneY::PlaneY(double y)
		: AbstractPlane(y, Axis3D::y)
	{

	}

	std::optional<double> PlaneY::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithPositiveFace(origin.y, end.y);
	}

	std::optional<double> PlaneY::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithNegativeFace(origin.y, end.y);
	}

	Vec3d PlaneY::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { Vec1d::Lerp(origin.x, end.x, time), GetPosition(), Vec1d::Lerp(origin.z, end.z, time) };
	}

	Vec3d PlaneY::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { end.x, Vec1d::MirrorPosition(end.y, intersection.y), end.z };
	}
}