#pragma once
#include "abstract_generating_plane_3d.h"

namespace accord::shape::generating
{
	class PlaneZ3D : public generating::AbstractPlane3D
	{
	public:
		PlaneZ3D(double z);

		Vec3d PlacePointOnPlane(const Vec2d& position) const;
	};
}