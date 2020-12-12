#pragma once
#include "basic_rect.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	class Rect : public basic::Rect, public Shape2D
	{
	public:
		Rect(Vec2d origin, Vec2d length);

		Vec2d GeneratePointInArea() const;

		void ToJson(Json& j) const;
	};
}