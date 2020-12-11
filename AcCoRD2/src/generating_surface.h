#pragma once
#include "pch.h"
#include "vec3d.h"
#include "generating_plane.h"
#include "generating_surface_shape.h"

namespace accord::shape::generating
{
	class Surface
	{
	public:
		Surface(Plane plane);

		Vec3d GeneratePointOnSurface() const;

		const Plane GetPlane() const;

		virtual const SurfaceShape& GetShape() const = 0;

	private:
		Plane plane;
	};

	void to_json(Json& j, const SurfaceShape& surface_shape);
}
