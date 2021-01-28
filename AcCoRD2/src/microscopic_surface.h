#pragma once
#include "microscopic_high_priority_relative_shape.h"
#include "microscopic_high_priority_relative.h"

namespace accord::microscopic
{
	class Surface : public HighPriorityRelative
	{
	public:
		Surface(std::unique_ptr<HighPriorityRelativeShape> shape, const SurfaceDirection& surface_direction);

		const HighPriorityRelativeShape& GetShape() const;

		// remove const SurfaceType&
		std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner,
			SurfaceType surface_type, int cycles, bool allowObstructions);

		const SurfaceDirection& GetSurfaceDirection() const;
	private:
		std::unique_ptr<HighPriorityRelativeShape> shape;
		SurfaceDirection surface_direction;
	};
}