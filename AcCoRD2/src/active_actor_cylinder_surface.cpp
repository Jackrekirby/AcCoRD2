// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "active_actor_cylinder_surface.h"

namespace accord
{
	ActiveActorCylinderSurface::ActiveActorCylinderSurface(const shape::basic::Cylinder& cylinder)
		: shape::generating::Cylinder(cylinder), shape::basic::Cylinder(cylinder), shape::relation::Cylinder(cylinder)
	{
	}

	Vec3d ActiveActorCylinderSurface::GenerateMolecule()
	{
		return shape::generating::Cylinder::GeneratePointOnSurface();
	}

	double ActiveActorCylinderSurface::CalculateVolume()
	{
		return shape::generating::Cylinder::CalculateSurfaceArea();
	}

	bool ActiveActorCylinderSurface::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Cylinder::IsOverlapping(other);
	}

	void ActiveActorCylinderSurface::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Cylinder>(*this);
	}
}