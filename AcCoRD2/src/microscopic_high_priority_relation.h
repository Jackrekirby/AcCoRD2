#pragma once
#include "pch.h"
#include "vec3d.h"
#include "collision_3d.h"
#include "microscopic_surface.h"
#include "molecule_destination.h"

// IDEA
// HighPriorityRelations should require an additional surfaces
// LowPriorityRelations should also have additional surface (could make reflecting bowl)
// neighbours should also require an additonal surface as it means a plane surface does not have to be drawn between them
// e.g. box and sphere allow diffusion between them but are reflecting other wise so put a None Surface Between Them
// could add an overriding non owning region to allow this behaviour without owning
// (another relationship type would be called surface overrider which overides the surface properties for that region)
// useful for curved surfaces, not so much for boxes where a plane surface can be attached

// surface types: reflecting, absorbing, adsorbing, membrane, none
// membrane simply has probability between reflecting and none

namespace accord::microscopic
{
	//class Surface;
	class Grid2;

	// A Grid owner is the object which currently owns a molecule during path checking.
	// A Owner owner is the object which will own the molecule at the end of diffusion.

	class HighPriorityRelation // High Priority Relation
	{
	public:
		// requires get surface type and get shape for collision checking
		virtual Surface& GetSurface() = 0;

		// each surface type can have its own pass molecule function so it can choose what to do with the molecule
		// absorbing surfaces return nullopt
		// adsorbing surfaces return intersection position and itself as owner
		// reflecting surfaces get current owner to call CheckMoleculePath() on reflected path
		// a neighbour will take ownership and call CheckMoleculePath()
		virtual std::optional<MoleculeDestination> PassMoleculeToHighPriorityRelation(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid2* owner) = 0;
	};
}