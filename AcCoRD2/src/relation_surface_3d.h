#pragma once
#include "relation_plane_3d.h"
#include "relation_surface_3d_shape.h"

namespace accord::shape::relation
{
	class Surface3D
	{
	public:
		Surface3D(Plane3D plane, std::unique_ptr<Surface3DShape> shape);

		bool IsPartiallyNeighbouring(const Surface3D& other) const;

		bool IsFullyNeighbouring(const Surface3D& other) const;

		const Plane3D& GetPlane() const;

		const Surface3DShape& GetShape() const;

	private:
		Plane3D plane;
		std::unique_ptr<Surface3DShape> shape;
	};

	void to_json(Json& j, const Surface3DShape& surface_shape);
}
