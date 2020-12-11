#include "pch.h"
#include "collision_rect_surface.h"

namespace accord::shape::collision
{
	RectSurface::RectSurface(Plane plane, Rect rect)
		: Surface(plane), rect(rect)
	{

	}

	const Rect& RectSurface::GetShape() const
	{
		return rect;
	}
}
