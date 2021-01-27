#pragma once
#include "basic_plane.h"
#include "basic_circle.h"

namespace accord::shape::basic
{
	class CircleSurface
	{
	public:
		CircleSurface(const Plane& plane, const Circle& circle);

		Plane plane;
		Circle circle;
	};
}
