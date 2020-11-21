#include "pch.h"
#include "generating_circle_surface.h"

namespace accord::shape::generating
{
	CircleSurface::CircleSurface(std::unique_ptr<AbstractPlane> plane, Circle circle)
		: Surface(std::move(plane)), circle(circle)
	{

	}

	const Circle& CircleSurface::GetShape() const
	{
		return circle;
	}
}
