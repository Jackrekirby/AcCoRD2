#pragma once
#include "pch.h"
#include "generating_surface_shape.h"

namespace accord::shape::generating
{
	void to_json(Json& j, const SurfaceShape& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}