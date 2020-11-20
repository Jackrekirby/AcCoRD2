#pragma once
#include "basic_box_2d.h"
#include "generating_surface_3d_shape.h"

namespace accord::shape::generating
{
	class Box2D : public basic::Box2D, public Surface3DShape
	{
	public:
		Box2D(Vec2d origin, Vec2d length);

		Vec2d GeneratePointInArea() const;

		void ToJson(Json& j) const;
	};
}