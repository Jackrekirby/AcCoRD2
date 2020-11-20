#include "pch.h"
#include "relation_circle_surface.h"

namespace accord::shape::relation
{
	RectSurface::RectSurface(Plane3D plane, Circle circle)
		: Surface(plane), circle(circle)
	{

	}

	const Circle& RectSurface::GetShape() const
	{
		return circle;
	}
}
