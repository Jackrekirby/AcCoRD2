#pragma once
#include "basic_rect.h"
#include "collision_shape_2d.h"

namespace accord::shape::collision
{
	// unlike collision circle collision rect does not implement a method to calculate molecule collisions in plane,
	// only whether a point lies inside the rectangle. Would be required for diffusion of a molecule on an adsorbing surface
	class Rect : public basic::Rect, public Shape2D
	{
	public:
		// define the rectangle either with primitive parameters or a basic rect
		Rect(Vec2d origin, Vec2d length);

		Rect(basic::Rect rect);

		// see basic rect
		bool IsWithinOrOnBorder(const Vec2d& position) const;

		void ToJson(Json& j) const;
	};
}