#pragma once
#include "pch.h"
#include "collision_circle_surface.h"
#include "microscopic_high_priority_relative_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class CircleSurfaceShape : public HighPriorityRelativeShape, public shape::collision::CircleSurface
	{
	public:

		CircleSurfaceShape(const shape::basic::CircleSurface& circle_surface);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;
	};
}
