#pragma once
#include "pch.h"
#include "collision_3d.h"
#include "basic_box.h"

// may not need to get surface type as surface is virtual so function will call required surface
// if each shape and type has its own class: BoxAbsorbingSurface, SphereReflectingSurface
// defintely need to know the type of shape as some surfaces can neighbour while other cant,
// you must put a box surface on a box region but the surface can be of any type.

// a region has its own internal surface and a surface per relationship type
namespace accord::microscopic
{
	// could just be a collision shape3D but may require other shape type functionality
	// consider seperating surface shape into one per relationship type
	class SurfaceShape
	{
	public:
		virtual std::optional<shape::collision::Collision3D> 
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		virtual bool IsMoleculeOnBorder(const Vec3d& position) const = 0;

		virtual shape::basic::Box GenerateBoundingBox() const = 0;
	};

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