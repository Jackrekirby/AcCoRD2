#include "pch.h"
#include "generating_shape_3d.h"

namespace accord::shape::generating
{
	void to_json(Json& j, const Shape3D& shape)
	{
		shape.ToJson(j);
	}
}