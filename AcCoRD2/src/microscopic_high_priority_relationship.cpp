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
