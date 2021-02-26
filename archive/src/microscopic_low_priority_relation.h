#pragma once
#include "pch.h"
#include "vec3d.h"
#include "collision_3d.h"
#include "microscopic_surface.h"
#include "molecule_destination.h"

namespace accord::microscopic
{
	class MoleculeDestination;
	class Grid;

	class LowPriorityRelation // High Priority Relation
	{
	public:
		// requires is molecule inside surface boundary and get surface type
		virtual Surface& GetSurface() = 0;

		// grids need to check if inside then pass ownership and continue path checking
		// meso regions need to check if inside and so stop path checking, return 
		virtual std::optional<MoleculeDestination> PassMoleculeToLowPriorityRelation(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner) = 0;
	};
}