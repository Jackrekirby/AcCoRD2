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

		const Circle& GetShape() const;
	private:
		Circle circle;
	};
}
