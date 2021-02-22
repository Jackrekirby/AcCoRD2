#pragma once
#include "collision_surface.h"
#include "collision_circle.h"

namespace accord::shape::basic
{
	class CircleSurface;
}

namespace accord::shape::collision
{
	// a circular surface, composed of a plane and circle
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
