#include "pch.h"
#include "generating_rect_surface.h"

namespace accord::shape::generating
{
	RectSurface::RectSurface(std::unique_ptr<AbstractPlane> plane, Rect rect)
		: Surface(std::move(plane)), rect(rect)
	{

	}

	const Rect& RectSurface::GetShape() const
	{
		return rect;
	}
}
