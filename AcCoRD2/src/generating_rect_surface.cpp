#include "pch.h"
#include "generating_rect_surface.h"

namespace accord::shape::generating
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
