#pragma once
#include "relation_plane.h"
#include "relation_surface_shape.h"

namespace accord::shape::relation
{
	class Surface
	{
	public:
		Surface(Plane3D plane);

		bool IsPartiallyNeighbouring(const Surface& other) const;

		bool IsFullyNeighbouring(const Surface& other) const;

		const Plane3D& GetPlane() const;

		virtual const SurfaceShape& GetShape() const = 0;

	private:
		Plane3D plane;
	};

	void to_json(Json& j, const SurfaceShape& surface_shape);
}
