#include "collision_plane_z.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneZ::PlaneZ(double z)
		: AbstractPlane(z, Axis3D::z)
	{

	}

	std::optional<double> PlaneZ::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{		
		return Plane1D::CalculateCollisionTimeWithPositiveFace(origin.z, end.z);
	}

	std::optional<double> PlaneZ::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithNegativeFace(origin.z, end.z);
	}

	Vec3d PlaneZ::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { Lerp(origin.x, end.x, time),  Lerp(origin.y, end.y, time), GetPosition() };
	}

	Vec3d PlaneZ::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { end.x, end.y,  MirrorPosition(end.z, intersection.z) };
	}
}