// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_low_priority_relationship.h"

namespace accord::microscopic
{
	class Grid;
	class RegionShape;

	LowPriorityRelationship::LowPriorityRelationship(LowPriorityRelative* relative, SurfaceType type)
		: relative(relative), type(type)
	{

	}

	SurfaceType LowPriorityRelationship::GetSurfaceType() const
	{
		return type;
	}

	LowPriorityRelative& LowPriorityRelationship::GetLowPriorityRelative() const
	{
		return *relative;
	}
}
