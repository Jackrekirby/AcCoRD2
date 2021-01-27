#include "pch.h"
#include "relation_rect_surface.h"
#include "basic_rect_surface.h"
#include "vec3d.h"

namespace accord::shape::relation
{
	RectSurface::RectSurface(Plane plane, Rect rect)
		: Surface(plane), rect(rect)
	{
		
	}

	RectSurface::RectSurface(const basic::RectSurface& rect_surface)
		: Surface(rect_surface.plane), rect(rect_surface.rect)
	{
		
	}

	basic::RectSurface RectSurface::ToBasic() const
	{
		return { GetPlane(), rect };
	}

	const Rect& RectSurface::GetShape() const
	{
		return rect;
	}
}
