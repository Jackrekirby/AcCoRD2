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
	class Grid;

	class Relative
	{
	public:

		virtual std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner,
			SurfaceType surface_type, int cycles, bool allowObstructions) = 0;
	};
}
