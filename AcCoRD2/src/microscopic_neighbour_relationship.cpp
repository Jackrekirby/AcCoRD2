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
