#pragma once
#include "microscopic_surface_type.h"

namespace accord::microscopic
{
	class LowPriorityRelative;

	class LowPriorityRelationship
	{
	public:
		LowPriorityRelationship(LowPriorityRelative* relative, SurfaceType type);

		SurfaceType GetSurfaceType() const;

		LowPriorityRelative& GetLowPriorityRelative() const;

	private: 
		SurfaceType type;
		LowPriorityRelative* relative;
	};
}
