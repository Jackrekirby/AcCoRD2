// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "collision_2d.h"

namespace accord::shape::collision
{
	Collision2D::Collision2D(double time, Vec2d intersection, Vec2d reflection)
		: time(time), intersection(intersection), reflection(reflection)
	{

	}
}