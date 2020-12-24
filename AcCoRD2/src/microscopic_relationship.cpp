#include "pch.h"
#include "microscopic_relationship.h"

namespace accord::microscopic
{
	class Grid;
	class SurfaceShape;

	Relationship::Relationship(Relative* relative, SurfaceType type)
		: relative(relative), type(type)
	{

	}

	SurfaceType Relationship::GetSurfaceType() const
	{
		return type;
	}

	Relative& Relationship::GetRelative() const
	{
		return *relative;
	}
}
