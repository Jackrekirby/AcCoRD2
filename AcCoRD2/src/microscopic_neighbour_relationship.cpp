// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_neighbour_relationship.h"

namespace accord::microscopic
{
	class Grid;
	class RegionShape;

	NeighbourRelationship::NeighbourRelationship(NeighbourRelative* relative, SurfaceType type)
		: relative(relative), type(type)
	{

	}

	SurfaceType NeighbourRelationship::GetSurfaceType() const
	{
		return type;
	}

	NeighbourRelative& NeighbourRelationship::GetNeighbourRelative() const
	{
		return *relative;
	}
}
