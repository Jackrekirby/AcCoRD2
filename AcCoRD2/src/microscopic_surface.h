// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_surface_type.h"
#include "microscopic_surface_shape.h"
#include "microscopic_high_priority_relative.h"
#include "microscopic_neighbour_relative.h"

namespace accord::microscopic
{
	class Surface : public HighPriorityRelative, public NeighbourRelative
	{
	public:
		Surface(std::unique_ptr<SurfaceShape> shape, const SurfaceDirection& surface_direction);

		const SurfaceShape& GetShape() const;

		// remove const SurfaceType&
		std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid* owner,
			SurfaceType surface_type, int cycles, bool allowObstructions);

		const SurfaceDirection& GetSurfaceDirection() const;

		bool IsRegion() const;
	private:
		std::unique_ptr<SurfaceShape> shape;
		SurfaceDirection surface_direction;
	};
}