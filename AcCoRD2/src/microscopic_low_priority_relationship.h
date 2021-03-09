// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_surface_type.h"

namespace accord::microscopic
{
	class LowPriorityRelative;

	class LowPriorityRelationship
	{
	public:
		LowPriorityRelationship(LowPriorityRelative* relative, SurfaceType type);

		SurfaceType GetSurfaceType() const;

		LowPriorityRelative& GetLowPriorityRelative() const;

	private: 
		SurfaceType type;
		LowPriorityRelative* relative;
	};
}
