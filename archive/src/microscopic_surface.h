#pragma once
#include "pch.h"

// may not need to get surface type as surface is virtual so function will call required surface
// if each shape and type has its own class: BoxAbsorbingSurface, SphereReflectingSurface
// defintely need to know the type of shape as some surfaces can neighbour while other cant,
// you must put a box surface on a box region but the surface can be of any type.

// a region has its own internal surface and a surface per relationship type


// NO LONGER NEED AS GRID CAN JUST CALL GET SURFACESHAPE
// SURFACE TYPE NO LONGER NEEDED IN SURFACE, BUT AS RELATION ATTRIBUTES

// THE SURFACE CLASS WILL BECOME SURFACES THAT ARE NO INHERITED BY REGIONS
// SURFACE WILL INHERITED FROM RELATIONS TYPES
namespace accord::microscopic
{
	class SurfaceShape;

	class Surface
	{
	public:

		enum class Type
		{
			Absorping, Adsorbing, Membrane, Reflecting, None
		};

		Surface(Type type);

		Type GetType() const;

		virtual SurfaceShape& GetShape() = 0;

	private:
		Type type;
	};
}