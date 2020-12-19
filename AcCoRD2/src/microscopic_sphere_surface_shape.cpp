#include "pch.h"
#include "microscopic_sphere_surface_shape.h"

namespace accord::microscopic
{
	SphereSurfaceShape::SphereSurfaceShape(Vec3d centre, double radius)
		: shape::collision::Sphere(centre, radius)
	{

	}

	std::optional<shape::collision::Collision3D>
		SphereSurfaceShape::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Sphere::CalculateExternalCollisionData(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		SphereSurfaceShape::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Sphere::CalculateInternalCollisionData(origin, end);
	}

	bool SphereSurfaceShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return shape::basic::Sphere::IsWithinOrOnBorder(position);
	}

	bool SphereSurfaceShape::IsMoleculeOnBorder(const Vec3d& position) const
	{
		LOG_CRITICAL("Sphere's Cannot Be Neighbours, Only High or Low Priority Relations");
		throw std::exception();
	}

	const shape::basic::Sphere& SphereSurfaceShape::GetBasicShape() const
	{
		return static_cast<const shape::basic::Sphere&>(*this);
	}
}
