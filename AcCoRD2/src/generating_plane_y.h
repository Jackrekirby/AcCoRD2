#pragma once
#include "abstract_generating_plane_3d.h"

namespace accord::shape::generating
{
	class PlaneY3D : public generating::AbstractPlane3D
	{
	public:
		PlaneY3D(double z);

		Vec3d PlacePointOnPlane(const Vec2d& position) const;

		Vec3d GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const;
	};
}