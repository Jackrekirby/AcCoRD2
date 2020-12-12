#include "pch.h"
#include "relation_rect_surface.h"

namespace accord::shape::relation
{
	RectSurface::RectSurface(Plane plane, Rect box)
		: Surface(plane), box(box)
	{

	}

	const Rect& RectSurface::GetShape() const
	{
		return box;
	}
}
