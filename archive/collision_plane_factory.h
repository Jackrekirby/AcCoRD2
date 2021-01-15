#pragma once
#include "abstract_collision_plane.h"

namespace accord::shape::collision
{
	std::unique_ptr<Plane> CreatePlane(double position, Axis3D axis);
}