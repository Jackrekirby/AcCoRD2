#pragma once
#include "collision_surface_3d.h"
#include "axis_3d.h"

namespace accord
{
	struct Vec2d;
	struct Vec3d;
}

namespace accord::shape::collision
{
	Surface3D CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end);

	Surface3D CreateBoxSurface(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
}
