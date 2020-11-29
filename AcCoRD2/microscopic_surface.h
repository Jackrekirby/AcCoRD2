#pragma once

// may not need to get surface type as surface is virtual so function will call required surface
// if each shape and type has its own class: BoxAbsorbingSurface, SphereReflectingSurface
// defintely need to know the type of shape as some surfaces can neighbour while other cant,
// you must put a box surface on a box region but the surface can be of any type.

// a region has its own internal surface and a surface per relationship type
namespace accord
{
	// could just be a collision shape3D but may require other shape type functionality
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

		virtual SurfaceShape& GetShape() const = 0;

	private:
		Type type;
	};
}