#include "pch.h"
#include "generating_circle_surface.h"
#include "basic_circle_surface.h"

namespace accord::shape::generating
{
	CircleSurface::CircleSurface(Plane plane, Circle circle)
		: Surface(plane), circle(circle)
	{

	}

	CircleSurface::CircleSurface(const basic::CircleSurface& circle_surface)
		: Surface(circle_surface.plane), circle(circle_surface.circle)
	{
	}

	const Circle& CircleSurface::GetShape() const
	{
		return circle;
	}
}
