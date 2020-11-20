#pragma once
#include "generating_surface.h"

namespace accord::shape::generating
{
	Surface3D CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end);

	Surface3D CreateBoxSurface(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
}
