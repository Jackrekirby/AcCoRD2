#pragma once
#include "basic_rect.h"
#include "generating_surface_shape.h"

namespace accord::shape::generating
{
	class Rect : public basic::Rect, public SurfaceShape
	{
	public:
		Rect(Vec2d origin, Vec2d length);

		Vec2d GeneratePointInArea() const;

		void ToJson(Json& j) const;
	};
}