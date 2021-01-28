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
	class LowPriorityRelativeShape
	{
	public:
		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;
	};
}