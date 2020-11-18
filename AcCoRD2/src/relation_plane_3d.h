#pragma once
#include "basic_plane_3d.h"
#include "vec3d.h"

namespace accord::shape::relation
{
	class Plane3D : public basic::AbstractPlane3D
	{
	public:
		Plane3D(double position, Axis3D axis);

		bool IsNeighbouring(const Plane3D& other) const;
	};

	void to_json(Json& j, const Plane3D& plane);
}