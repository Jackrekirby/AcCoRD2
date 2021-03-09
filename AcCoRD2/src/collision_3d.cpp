// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "collision_3d.h"

namespace accord::shape::collision
{
	Collision3D::Collision3D(double time, Vec3d intersection, Vec3d reflection)
		: time(time), intersection(intersection), reflection(reflection)
	{

	}
}