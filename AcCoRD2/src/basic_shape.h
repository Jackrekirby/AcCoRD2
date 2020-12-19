#pragma once
#include "pch.h"

namespace accord::shape::basic
{
	class Shape
	{
	public:
		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Shape& shape);
}