#pragma once
#include "basic_box_2d.h"
#include "collision_surface_3d_shape.h"

namespace accord::shape::collision
{
	class Box2D : public basic::Box2D, public Surface3DShape
	{
	public:
		Box2D(Vec2d origin, Vec2d length);

		bool IsWithinBorder(const Vec2d& position) const;

		bool IsWithinOrOnBorder(const Vec2d& position) const;

		bool IsOnBorder(const Vec2d& position) const;

		void ToJson(Json& j) const;
	};
}