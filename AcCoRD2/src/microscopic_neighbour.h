#pragma once
#include "pch.h"
#include "vec3d.h"
#include "microscopic_surface.h"
#include "molecule_destination.h"

namespace accord::shape::collision
{
	class Collision3D;
}
namespace accord::microscopic
{
	class Grid2;

	class Neighbour // High Priority Relation
	{
	public:
		// requires is molecule on surface boundary and get surface type
		virtual Surface& GetSurface() = 0;

		// grids need to check if on boundary then pass ownership and continue path checking
		// meso regions need to check on boundary and so stop path checking, return 
		// a surface (NOT A PSEUDO ONE) needs to check if in area then respond accordingly.
		virtual std::optional<MoleculeDestination> PassMoleculeToNeighbour(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid2* owner) = 0;
	};
}