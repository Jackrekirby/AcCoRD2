#pragma once
#include "abstract_collision_plane_3d.h"

namespace accord::shape::collision
{
	std::unique_ptr<AbstractPlane3D> CreatePlane(double position, Axis3D axis);
}