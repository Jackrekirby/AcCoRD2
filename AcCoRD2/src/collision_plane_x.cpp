#include "collision_plane_x.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneX::PlaneX(double x)
		: AbstractPlane(x, Axis3D::x)
	{

	}

	std::optional<double> PlaneX::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithPositiveFace(origin.x, end.x);
	}

	std::optional<double> PlaneX::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithNegativeFace(origin.x, end.x);
	}

	Vec3d PlaneX::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { GetPosition(), Vec1d::Lerp(origin.y, end.y, time),  Vec1d::Lerp(origin.z, end.z, time) };
	}

	Vec3d PlaneX::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { Vec1d::MirrorPosition(end.x, intersection.x), end.y, end.z };
	}
}