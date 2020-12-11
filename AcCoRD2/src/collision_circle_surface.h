#pragma once
#include "collision_surface.h"
#include "collision_circle.h"

namespace accord::shape::collision
{
	class CircleSurface : public Surface
	{
	public:
		CircleSurface(Plane plane, Circle circle);

		const Circle& GetShape() const;

	private:
		Circle circle;
	};
}
