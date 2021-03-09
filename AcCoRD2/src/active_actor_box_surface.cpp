// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "active_actor_box_surface.h"

namespace accord
{
	ActiveActorBoxSurface::ActiveActorBoxSurface(const Vec3d& origin, const Vec3d& length)
		: shape::generating::Box(origin, length), shape::basic::Box(origin, length), shape::relation::Box(origin, length)
	{

	}

	ActiveActorBoxSurface::ActiveActorBoxSurface(const shape::basic::Box& box)
		: shape::generating::Box(box), shape::basic::Box(box), shape::relation::Box(box)
	{
	}

	Vec3d ActiveActorBoxSurface::GenerateMolecule()
	{
		return shape::generating::Box::GeneratePointOnSurface();
	}

	double ActiveActorBoxSurface::CalculateVolume()
	{
		return shape::generating::Box::CalculateSurfaceArea();
	}

	bool ActiveActorBoxSurface::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Box::IsOverlapping(other);
	}

	void ActiveActorBoxSurface::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Box>(*this);
	}
}