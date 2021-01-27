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
