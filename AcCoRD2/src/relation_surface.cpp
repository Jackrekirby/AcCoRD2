// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "relation_surface.h"

namespace accord::shape::relation
{

	Surface::Surface(Plane plane)
		: plane(plane)
	{

	}

	bool Surface::IsPartiallyNeighbouring(const Surface& other) const
	{
		//LOG_INFO("plane = {},  {}", GetPlane().GetPosition(), other.GetPlane().GetPosition());
		return (GetPlane().IsNeighbouring(other.GetPlane()) && GetShape().IsOverlapping(other.GetShape()));
	}

	bool Surface::IsFullyNeighbouring(const Surface& other) const
	{
		return (GetPlane().IsNeighbouring(other.GetPlane()) && GetShape().IsEnveloping(other.GetShape()));
	}

	const Plane& Surface::GetPlane() const
	{
		return plane;
	}

	void to_json(Json& j, const Surface& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
