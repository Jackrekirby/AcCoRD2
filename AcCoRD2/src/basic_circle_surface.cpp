#include "pch.h"
#include "basic_circle_surface.h"

namespace accord::shape::basic
{
	CircleSurface::CircleSurface(const Plane& plane, const Circle& circle)
		: plane(plane), circle(circle)
	{

	}
}