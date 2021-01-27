#pragma once
#include "basic_plane.h"
#include "basic_circle.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::shape::basic
{
	class CircleSurface
	{
	public:
		CircleSurface(const Plane& plane, const Circle& circle);

		CircleSurface(const Vec3d& centre, double radius, const Axis3D& axis);

		Plane plane;
		Circle circle;
	};
}
