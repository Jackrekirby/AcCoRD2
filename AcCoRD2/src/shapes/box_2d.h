#pragma once
#include "math/vec2d.h"
#include "surface_3d_shape.h"

namespace accord::shapes
{
	class Box2D : public Surface3DShape
	{
	public:
		Box2D(math::Vec2d origin, math::Vec2d length);

		void Move(const math::Vec2d& origin);

		void Resize(const math::Vec2d& length);

		bool IsWithinBorder(const math::Vec2d& position) const;

		bool IsWithinOrOnBorder(const math::Vec2d& position) const;

		bool IsOnBorder(const math::Vec2d& position) const;
	private:
		math::Vec2d origin;
		math::Vec2d end;
		math::Vec2d length;
	};
}