#include "pch.h"
#include "collision_circle_surface.h"

namespace accord::shape::collision
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
