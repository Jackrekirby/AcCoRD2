// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_rect.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	class Rect : public basic::Rect, public Shape2D
	{
	public:
		Rect(Vec2d origin, Vec2d length);

		Rect(basic::Rect rect);

		Vec2d GeneratePointInArea() const;

		void ToJson(Json& j) const;
	};
}