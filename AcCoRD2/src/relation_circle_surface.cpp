// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "relation_circle_surface.h"
#include "basic_circle_surface.h"

namespace accord::shape::relation
{
	CircleSurface::CircleSurface(Plane plane, Circle circle)
		: Surface(plane), circle(circle)
	{

	}

	CircleSurface::CircleSurface(const basic::CircleSurface& circle_surface)
		: Surface(circle_surface.plane), circle(circle_surface.circle)
	{
	}

	basic::CircleSurface CircleSurface::ToBasic() const
	{
		return { GetPlane(), circle };
	}

	const Circle& CircleSurface::GetShape() const
	{
		return circle;
	}
}
