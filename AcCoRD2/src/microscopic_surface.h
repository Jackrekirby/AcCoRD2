#pragma once
#include "microscopic_surface_shape.h"
#include "microscopic_relative.h"

namespace accord::microscopic
{
	class Surface : public Relative
	{
	public:
		Surface(std::unique_ptr<SurfaceShape> shape, const SurfaceDirection& surface_direction);

		const SurfaceShape& GetShape() const;

		// remove const SurfaceType&
		std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner,
			SurfaceType surface_type, int cycles, bool allowObstructions);

		const SurfaceDirection& GetSurfaceDirection() const;
	private:
		std::unique_ptr<SurfaceShape> shape;
		SurfaceDirection surface_direction;
	};
}