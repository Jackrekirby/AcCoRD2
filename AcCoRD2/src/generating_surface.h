#pragma once
#include "pch.h"
#include "vec3d.h"
#include "abstract_generating_plane.h"
#include "generating_surface_shape.h"

namespace accord::shape::generating
{
	class Surface
	{
	public:
		Surface(std::unique_ptr<AbstractPlane> plane);

		Vec3d GeneratePointOnSurface() const;

		const AbstractPlane& GetPlane() const;

		virtual const SurfaceShape& GetShape() const = 0;

	private:
		std::unique_ptr<AbstractPlane> plane;
	};

	void to_json(Json& j, const SurfaceShape& surface_shape);
}
