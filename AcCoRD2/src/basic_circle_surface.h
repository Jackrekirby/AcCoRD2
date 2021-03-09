// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_plane.h"
#include "basic_circle.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::shape::basic
{
	class CircleSurface
	{
	public:
		CircleSurface(const Plane& plane, const Circle& circle);

		CircleSurface(const Vec3d& centre, double radius, const Axis3D& axis);

		Plane plane;
		Circle circle;
	};
}
