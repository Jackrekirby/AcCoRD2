#pragma once
#include "pch.h"
#include "vec2d.h"

namespace accord::shape::relation
{
	class Surface3DShape
	{
	public:
		Surface3DShape() = default;

		virtual bool IsOverlapping(const Surface3DShape& other) const = 0;

		virtual bool IsEnveloping(const Surface3DShape& other) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Surface3DShape& surface_shape);
}