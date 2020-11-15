#include "plane_z_3d.h"
#include "math/vec1d.h"

namespace accord::shapes
{
	PlaneZ_3D::PlaneZ_3D(double z)
		: AbstractPlane3D(z, math::Axis3D::z)
	{

	}

	std::optional<double> PlaneZ_3D::CalculateCollisionTimeWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end) const
	{		
		return Plane::CalculateCollisionTimeWithPositiveFace(origin.z, end.z);
	}

	std::optional<double> PlaneZ_3D::CalculateCollisionTimeWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end) const
	{
		return Plane::CalculateCollisionTimeWithNegativeFace(origin.z, end.z);
	}

	math::Vec3d PlaneZ_3D::CalculateIntersection(const math::Vec3d& origin, const math::Vec3d& end, double time) const
	{
		return { math::Lerp(origin.x, end.x, time),  math::Lerp(origin.y, end.y, time), position };
	}

	math::Vec3d PlaneZ_3D::CalculateReflection(const math::Vec3d& intersection, const math::Vec3d& end) const
	{
		return { end.x, end.y,  math::MirrorPosition(end.z, intersection.z) };
	}
}