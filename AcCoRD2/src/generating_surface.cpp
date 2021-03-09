// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "generating_surface.h"

namespace accord::shape::generating
{

	Surface::Surface(Plane plane)
		: plane(plane)
	{

	}

	Vec3d Surface::GeneratePointOnSurface() const
	{
		return plane.PlacePointOnPlane(GetShape().GeneratePointInArea());
	}

	const Plane Surface::GetPlane() const
	{
		return plane;
	}

	void to_json(Json& j, const Surface& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
