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
