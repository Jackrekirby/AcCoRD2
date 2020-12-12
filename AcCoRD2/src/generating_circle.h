#pragma once
#include "basic_circle.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	class Circle : public basic::Circle, public Shape2D
	{
	public:
		Circle(Vec2d centre, double radius);

		Vec2d GeneratePointInArea() const;

		Vec2d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}