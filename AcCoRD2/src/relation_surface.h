#pragma once
#include "relation_plane.h"
#include "relation_shape_2d.h"

namespace accord::shape::relation
{
	class Surface
	{
	public:
		Surface(Plane plane);

		bool IsPartiallyNeighbouring(const Surface& other) const;

		bool IsFullyNeighbouring(const Surface& other) const;

		const Plane& GetPlane() const;

		virtual const Shape2D& GetShape() const = 0;

	private:
		Plane plane;
	};

	void to_json(Json& j, const Shape2D& surface_shape);
}
