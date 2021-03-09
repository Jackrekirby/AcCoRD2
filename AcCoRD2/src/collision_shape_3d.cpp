// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "collision_shape_3d.h"

namespace accord::shape::collision
{
	void to_json(Json& j, const Shape3D& shape)
	{
		shape.ToJson(j);
	}
}