// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "generating_surface.h"
#include "generating_circle.h"

namespace accord::shape::basic
{
	class CircleSurface;
}

namespace accord::shape::generating
{
	class CircleSurface : public Surface
	{
	public:
		CircleSurface(Plane plane, Circle circle);

		CircleSurface(const basic::CircleSurface& circle_surface);

		const Circle& GetShape() const;
	private:
		Circle circle;
	};
}
