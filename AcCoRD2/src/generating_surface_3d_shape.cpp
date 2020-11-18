#pragma once
#include "pch.h"
#include "generating_surface_3d_shape.h"

namespace accord::shape::generating
{
	void to_json(Json& j, const Surface3DShape& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}