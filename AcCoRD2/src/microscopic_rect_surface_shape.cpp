#include "pch.h"
#include "microscopic_rect_surface_shape.h"
#include "basic_rect_surface.h"

namespace accord::microscopic
{
	RectSurfaceShape::RectSurfaceShape(const shape::basic::RectSurface& rect_surface)
		: shape::collision::RectSurface(rect_surface)
	{

	}

	std::optional<shape::collision::Collision3D>
		RectSurfaceShape::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::RectSurface::CalculateCollisionDataWithPositiveFace(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		RectSurfaceShape::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::RectSurface::CalculateCollisionDataWithNegativeFace(origin, end);
	}
}
