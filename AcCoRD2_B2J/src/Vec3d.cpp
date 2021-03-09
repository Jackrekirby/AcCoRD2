// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "vec3d.h"

namespace accord
{
	void to_json(Json& j, const Vec3d& v)
	{
		j = { v.x, v.y, v.z };
	}
}