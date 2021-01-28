#pragma once
#include "pch.h"

namespace accord::shape::collision
{
	class Collision3D;
}
namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class NeighbourRelativeShape
	{
	public:
		virtual bool IsMoleculeOnBorder(const Vec3d& position) const = 0;
	};
}