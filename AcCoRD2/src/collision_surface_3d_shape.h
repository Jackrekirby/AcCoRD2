#pragma once
#include "pch.h"

namespace accord
{
	struct Vec2d;
}

namespace accord::shape::collision
{
	class Surface3DShape
	{
	public:
		Surface3DShape() = default;

		virtual bool IsWithinOrOnBorder(const Vec2d& position) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Surface3DShape& surface_shape);
}