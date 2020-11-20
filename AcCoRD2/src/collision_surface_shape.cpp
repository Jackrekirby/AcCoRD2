#pragma once
#include "pch.h"
#include "collision_surface_shape.h"

namespace accord::shape::collision
{
	void to_json(Json& j, const SurfaceShape& surface_shape)
	{
		surface_shape.ToJson(j);
	}
}