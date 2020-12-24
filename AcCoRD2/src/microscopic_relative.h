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
	class Relationship;
	class Grid;

	class Relative
	{
	public:
		virtual SurfaceType GetDefaultSurfaceType() const = 0;

		virtual const SurfaceShape& GetShape() const = 0;
		
		// remove const SurfaceType&
		virtual std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner, 
			 SurfaceType surface_type, int cycles, bool allowObstructions) = 0;

		virtual std::vector<Relationship>& GetNeighbourRelationships() = 0;

		virtual std::vector<Relationship>& GetLowPriorityRelationships() = 0;

		virtual std::vector<Relationship>& GetHighPriorityRelationships() = 0;
	};
}