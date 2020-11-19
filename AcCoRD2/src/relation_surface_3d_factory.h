#pragma once
#include "relation_surface_3d.h"

namespace accord
{
	struct Vec3d;
	struct Vec2d;
}

namespace accord::shape::relation
{
	Surface3D CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end);

	Surface3D CreateBoxSurface(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
}
