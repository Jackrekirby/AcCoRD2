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
	class HighPriorityRelativeShape
	{
	public:
		virtual std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;
	};
}