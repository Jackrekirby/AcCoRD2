#include "pch.h"
#include "basic_shape.h"

namespace accord::shape::basic
{
	void to_json(Json& j, const Shape& shape)
	{
		shape.ToJson(j);
	}
}