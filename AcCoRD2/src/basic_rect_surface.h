#pragma once
#include "basic_plane.h"
#include "basic_rect.h"

namespace accord::shape::basic
{
	class RectSurface
	{
	public:
		RectSurface(const Plane& plane, const Rect& rect);

		Plane plane;
		Rect rect;
	};
}