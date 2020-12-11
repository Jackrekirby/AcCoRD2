#include "pch.h"
#include "collision_circle_surface.h"

namespace accord::shape::collision
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
