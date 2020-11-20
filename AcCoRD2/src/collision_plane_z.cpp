#include "collision_plane_z_3d.h"
#include "vec1d.h"

namespace accord::shape::collision
{
	PlaneZ3D::PlaneZ3D(double z)
		: AbstractPlane3D(z, Axis3D::z)
	{

	}

	std::optional<double> PlaneZ3D::CalculateCollisionTimeWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{		
		return Plane1D::CalculateCollisionTimeWithPositiveFace(origin.z, end.z);
	}

	std::optional<double> PlaneZ3D::CalculateCollisionTimeWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		return Plane1D::CalculateCollisionTimeWithNegativeFace(origin.z, end.z);
	}

	Vec3d PlaneZ3D::CalculateIntersection(const Vec3d& origin, const Vec3d& end, double time) const
	{
		return { Lerp(origin.x, end.x, time),  Lerp(origin.y, end.y, time), GetPosition() };
	}

	Vec3d PlaneZ3D::CalculateReflection(const Vec3d& intersection, const Vec3d& end) const
	{
		return { end.x, end.y,  MirrorPosition(end.z, intersection.z) };
	}
}