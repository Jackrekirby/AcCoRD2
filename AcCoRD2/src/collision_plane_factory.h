#pragma once
#include "abstract_collision_plane.h"

namespace accord::shape::collision
{
	std::unique_ptr<AbstractPlane> CreatePlane(double position, Axis3D axis);
}