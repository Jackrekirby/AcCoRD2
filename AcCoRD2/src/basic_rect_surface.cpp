#include "pch.h"
#include "basic_rect_surface.h"

namespace accord::shape::basic
{	
	RectSurface::RectSurface(const Plane& plane, const Rect& rect)
		: plane(plane), rect(rect)
	{

	}
}