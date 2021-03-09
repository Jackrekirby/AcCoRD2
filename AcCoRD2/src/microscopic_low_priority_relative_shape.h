// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord::shape::collision
{
	class Collision3D;
}
namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class LowPriorityRelativeShape
	{
	public:
		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;
	};
}