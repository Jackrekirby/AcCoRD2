#pragma once
#include "pch.h"
#include "vec3d.h"
#include "abstract_generating_plane_3d.h"
#include "generating_surface_3d_shape.h"

namespace accord::shape::generating
{
	class Surface3D
	{
	public:
		Surface3D(std::unique_ptr<AbstractPlane3D> plane);

		Vec3d GeneratePointOnSurface() const;

		const AbstractPlane3D& GetPlane() const;

		virtual const Surface3DShape& GetShape() const = 0;

	private:
		std::unique_ptr<AbstractPlane3D> plane;
	};

	void to_json(Json& j, const Surface3DShape& surface_shape);
}
