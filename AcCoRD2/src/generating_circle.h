#pragma once
#include "basic_circle.h"
#include "generating_surface_3d_shape.h"

namespace accord::shape::generating
{
	class Circle : public basic::Circle, public Surface3DShape
	{
	public:
		Circle(Vec2d centre, double radius);

		Vec2d GeneratePointInArea() const;

		Vec2d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}