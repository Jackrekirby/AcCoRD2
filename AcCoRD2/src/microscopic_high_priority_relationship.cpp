// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_high_priority_relationship.h"

namespace accord::microscopic
{
	class Grid;
	class RegionShape;

	HighPriorityRelationship::HighPriorityRelationship(HighPriorityRelative* relative, SurfaceType type)
		: relative(relative), type(type)
	{

	}

	SurfaceType HighPriorityRelationship::GetSurfaceType() const
	{
		return type;
	}

	HighPriorityRelative& HighPriorityRelationship::GetHighPriorityRelative() const
	{
		return *relative;
	}
}
