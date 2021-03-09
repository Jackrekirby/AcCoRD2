// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec2d.h"

namespace accord::shape::generating
{
	class Shape2D
	{
	public:
		Shape2D() = default;

		virtual Vec2d GeneratePointInArea() const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Shape2D& shape);
}