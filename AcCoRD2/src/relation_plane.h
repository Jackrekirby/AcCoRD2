#pragma once
#include "basic_plane.h"

namespace accord::shape::relation
{
	class Plane3D : public basic::AbstractPlane
	{
	public:
		Plane3D(double position, Axis3D axis);

		bool IsNeighbouring(const Plane3D& other) const;
	};

	void to_json(Json& j, const Plane3D& plane);
}