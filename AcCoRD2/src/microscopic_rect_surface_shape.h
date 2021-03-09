// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "collision_rect_surface.h"
#include "microscopic_surface_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class RectSurfaceShape : public SurfaceShape, public shape::collision::RectSurface
	{
	public:

		RectSurfaceShape(const shape::basic::RectSurface& rect_surface);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		bool IsMoleculeOnBorder(const Vec3d& position) const;
	};
}
