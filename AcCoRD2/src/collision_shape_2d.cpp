#include "pch.h"
#include "collision_shape_2d.h"

namespace accord::shape::collision
{
	void to_json(Json& j, const Shape2D& shape)
	{
		shape.ToJson(j);
	}
}