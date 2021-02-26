#pragma once
#include "microscopic_surface_type.h"

namespace accord::microscopic
{
	class Relative;

	// relationship contains the attributes of the relationship a pointer to one of the relatives.
	class Relationship
	{
	public:
		Relationship(Relative* relative, SurfaceType type);

		SurfaceType GetSurfaceType() const;

		Relative& GetRelative() const;

	private: 
		SurfaceType type;
		Relative* relative;
	};
}
