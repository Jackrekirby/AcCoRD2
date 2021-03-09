// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_circle.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	class Circle : public basic::Circle, public Shape2D
	{
	public:
		Circle(Vec2d centre, double radius);

		Circle(basic::Circle circle);

		Vec2d GeneratePointInArea() const;

		Vec2d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}