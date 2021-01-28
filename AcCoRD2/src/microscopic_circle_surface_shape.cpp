#include "pch.h"
#include "microscopic_circle_surface_shape.h"
#include "basic_circle_surface.h"

namespace accord::microscopic
{
	CircleSurfaceShape::CircleSurfaceShape(const shape::basic::CircleSurface& circle_surface)
		: shape::collision::CircleSurface(circle_surface)
	{

	}

	std::optional<shape::collision::Collision3D>
		CircleSurfaceShape::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::CircleSurface::CalculateCollisionDataWithPositiveFace(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		CircleSurfaceShape::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::CircleSurface::CalculateCollisionDataWithNegativeFace(origin, end);
	}
	bool CircleSurfaceShape::IsMoleculeOnBorder(const Vec3d& position) const
	{
		return shape::collision::CircleSurface::GetShape().IsWithinOrOnBorder(position.GetPlane(shape::collision::CircleSurface::GetPlane().GetAxis()));
	}
}
