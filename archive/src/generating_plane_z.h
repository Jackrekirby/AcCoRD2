#pragma once
#include "abstract_generating_plane.h"

namespace accord::shape::generating
{
	class PlaneZ : public generating::Plane
	{
	public:
		PlaneZ(double z);

		Vec3d PlacePointOnPlane(const Vec2d& position) const;

		Vec3d GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const;
	};
}