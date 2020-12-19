#pragma once
#include "molecule_destination.h"
#include "microscopic_surface_type.h"

namespace accord::shape::collision
{
	class Collision3D;
}
namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class SurfaceShape;
	class Grid2;

	class Relative
	{
	public:
		virtual SurfaceType GetDefaultSurfaceType() const = 0;

		virtual const SurfaceShape& GetShape() const = 0;
		
		// remove const SurfaceType&
		virtual std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid2* owner, 
			 SurfaceType surface_type, int cycles) = 0;
	};
}