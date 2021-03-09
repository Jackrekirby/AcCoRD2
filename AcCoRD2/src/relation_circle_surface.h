// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "relation_surface.h"
#include "relation_circle.h"


namespace accord::shape::basic
{
	class CircleSurface;
}

namespace accord::shape::relation
{
	class CircleSurface : public Surface
	{
	public:
		CircleSurface(Plane plane, Circle circle);

		CircleSurface(const basic::CircleSurface& circle_surface);

		basic::CircleSurface ToBasic() const;

		const Circle& GetShape() const;
	private:
		Circle circle;
	};
}
