// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "relation_surface.h"
#include "relation_rect.h"

namespace accord::shape::basic
{
	class RectSurface;
}

namespace accord::shape::relation
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(Plane plane, Rect rect);

		RectSurface(const basic::RectSurface& rect_surface);

		basic::RectSurface ToBasic() const;

		const Rect& GetShape() const;
	private:
		Rect rect;
	};
}
