#include "pch.h"
#include "generating_circle_surface.h"

namespace accord::shape::generating
{
	CircleSurface::CircleSurface(Plane plane, Circle circle)
		: Surface(plane), circle(circle)
	{

	}

	const Circle& CircleSurface::GetShape() const
	{
		return circle;
	}
}
