#pragma once
#include "vec2d.h"

namespace accord::shape::generating
{
	class Surface3DShape
	{
	public:
		Surface3DShape() = default;

		virtual Vec2d GeneratePointOnSurface() const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Surface3DShape& surface_shape);
}