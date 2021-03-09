// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_surface_type.h"

namespace accord::microscopic
{
	class HighPriorityRelative;

	class HighPriorityRelationship
	{
	public:
		HighPriorityRelationship(HighPriorityRelative* relative, SurfaceType type);

		SurfaceType GetSurfaceType() const;

		HighPriorityRelative& GetHighPriorityRelative() const;

	private: 
		SurfaceType type;
		HighPriorityRelative* relative;
	};
}
