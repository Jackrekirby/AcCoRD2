// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "generating_circle.h"
#include "constants.h"

namespace accord::shape::generating
{
	Circle::Circle(Vec2d centre, double radius)
		: basic::Circle(centre, radius), Shape2D()
	{

	}

	Circle::Circle(basic::Circle circle)
		: basic::Circle(circle)
	{

	}

	Vec2d Circle::GeneratePointInArea() const
	{
		return (GetCentre() + Vec2d::GenerateRandomPolar() * GetRadius());
	}

	Vec2d Circle::GeneratePointOnSurface() const
	{
		return (GetCentre() + Vec2d::GenerateRandomPolar(GetRadius()));
	}

	void Circle::ToJson(Json& j) const
	{
		j = static_cast<basic::Circle>(*this);
	}
}
