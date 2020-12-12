#include "pch.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	void to_json(Json& j, const Shape2D& shape)
	{
		shape.ToJson(j);
	}
}