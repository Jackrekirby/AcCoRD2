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
