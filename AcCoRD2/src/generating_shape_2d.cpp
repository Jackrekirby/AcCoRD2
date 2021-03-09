// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	void to_json(Json& j, const Shape2D& shape)
	{
		shape.ToJson(j);
	}
}