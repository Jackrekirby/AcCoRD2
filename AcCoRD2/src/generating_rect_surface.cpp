#include "pch.h"
#include "generating_rect_surface.h"

namespace accord::shape::generating
{
	RectSurface::RectSurface(std::unique_ptr<AbstractPlane> plane, Rect box)
		: Surface(std::move(plane)), box(box)
	{

	}

	const Rect& RectSurface::GetShape() const
	{
		return box;
	}
}
