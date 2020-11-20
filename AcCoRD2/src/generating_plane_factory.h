#pragma once
#include "abstract_generating_plane_3d.h"

namespace accord::shape::generating
{
	std::unique_ptr<AbstractPlane3D> CreatePlane(double position, Axis3D axis);
}