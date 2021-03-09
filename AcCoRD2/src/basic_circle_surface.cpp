// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "basic_circle_surface.h"
#include "vec3d.h"

namespace accord::shape::basic
{
	CircleSurface::CircleSurface(const Plane& plane, const Circle& circle)
		: plane(plane), circle(circle)
	{

	}

	CircleSurface::CircleSurface(const Vec3d& centre, double radius, const Axis3D& axis)
		: plane(centre.GetAxis(axis), axis), circle(centre.GetPlane(axis), radius)
	{

	}
}