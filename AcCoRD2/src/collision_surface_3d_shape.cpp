#pragma once
#include "pch.h"
#include "surface_3d_shape.h"

namespace accord::shape::collision
{
	void to_json(Json& j, const Surface3DShape& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}