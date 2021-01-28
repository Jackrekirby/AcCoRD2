#pragma once
#include "microscopic_surface_shape.h"
#include "microscopic_relative.h"

namespace accord::microscopic
{
	class Surface : public Relative
	{
	public:
		SurfaceType GetDefaultSurfaceType() const;

		const SurfaceShape& GetShape() const;

		// remove const SurfaceType&
		std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner,
			SurfaceType surface_type, int cycles, bool allowObstructions);

		std::vector<Relationship>& GetNeighbourRelationships();

		std::vector<Relationship>& GetLowPriorityRelationships();

		std::vector<Relationship>& GetHighPriorityRelationships();
	private:
		std::unique_ptr<SurfaceShape> shape;
	};
}