// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_box_surface_shape2.h"

namespace accord::microscopic
{
	BoxSurfaceShape2::BoxSurfaceShape2(Vec3d origin, Vec3d length)
		: shape::collision::Box(origin, length),
		shape::basic::Box(origin, length)
	{

	}

	BoxSurfaceShape2::BoxSurfaceShape2(shape::basic::Box box)
		: shape::collision::Box(box),
		shape::basic::Box(box)
	{

	}

	std::optional<shape::collision::Collision3D>
		BoxSurfaceShape2::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Box::CalculateExternalCollisionData(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		BoxSurfaceShape2::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Box::CalculateInternalCollisionData(origin, end);
	}

	bool BoxSurfaceShape2::IsMoleculeOnBorder(const Vec3d& position) const
	{
		return shape::basic::Box::IsOnBorder(position);
	}
}
