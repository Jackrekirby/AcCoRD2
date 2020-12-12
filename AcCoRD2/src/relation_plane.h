#pragma once
#include "basic_plane.h"

namespace accord::shape::relation
{
	class Plane : public basic::Plane
	{
	public:
		Plane(double position, Axis3D axis);

		bool IsNeighbouring(const Plane& other) const;
	};

	void to_json(Json& j, const Plane& plane);
}