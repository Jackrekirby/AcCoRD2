// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_surface_type.h"

namespace accord::microscopic
{
	class NeighbourRelative;

	class NeighbourRelationship
	{
	public:
		NeighbourRelationship(NeighbourRelative* relative, SurfaceType type);

		SurfaceType GetSurfaceType() const;

		NeighbourRelative& GetNeighbourRelative() const;

	private: 
		SurfaceType type;
		NeighbourRelative* relative;
	};
}
