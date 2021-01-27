#include "pch.h"
#include "collision_circle_surface.h"
#include "basic_circle_surface.h"

namespace accord::shape::collision
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
