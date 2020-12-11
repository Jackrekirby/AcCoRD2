#include "pch.h"
#include "relation_circle_surface.h"

namespace accord::shape::relation
{
	CircleSurface::CircleSurface(Plane3D plane, Circle circle)
		: Surface(plane), circle(circle)
	{

	}

	const Circle& CircleSurface::GetShape() const
	{
		return circle;
	}
}
