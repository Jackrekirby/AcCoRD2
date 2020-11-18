#pragma once
#include "generating_surface_3d.h"

namespace accord::shape::generating
{
	Surface3D CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end);

	Surface3D CreateBoxSurface(Vec3d position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
}
