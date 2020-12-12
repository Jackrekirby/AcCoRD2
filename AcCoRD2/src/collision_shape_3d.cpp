#include "pch.h"
#include "collision_shape_3d.h"

namespace accord::shape::collision
{
	void to_json(Json& j, const Shape3D& shape)
	{
		shape.ToJson(j);
	}
}