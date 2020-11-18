#pragma once
#include "abstract_generating_plane_3d.h"

namespace accord::shape::generating
{
	class PlaneX3D : public generating::AbstractPlane3D
	{
	public:
		PlaneX3D(double x);

		Vec3d PlacePointOnPlane(const Vec2d& position) const;
	};
}