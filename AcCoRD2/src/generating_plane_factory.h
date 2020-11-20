#pragma once
#include "abstract_generating_plane.h"

namespace accord::shape::generating
{
	std::unique_ptr<AbstractPlane> CreatePlane(double position, Axis3D axis);
}