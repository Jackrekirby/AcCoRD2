#pragma once
#include "basic_rect.h"
#include "collision_shape_2d.h"

namespace accord::shape::collision
{
	class Rect : public basic::Rect, public Shape2D
	{
	public:
		Rect(Vec2d origin, Vec2d length);

		bool IsWithinOrOnBorder(const Vec2d& position) const;

		void ToJson(Json& j) const;
	};
}