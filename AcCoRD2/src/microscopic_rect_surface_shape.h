#pragma once
#include "pch.h"
#include "collision_rect_surface.h"
#include "microscopic_high_priority_relative_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class RectSurfaceShape : public HighPriorityRelativeShape, public shape::collision::RectSurface
	{
	public:

		RectSurfaceShape(const shape::basic::RectSurface& rect_surface);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;
	};
}
