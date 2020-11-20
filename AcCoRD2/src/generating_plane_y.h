#pragma once
#include "abstract_generating_plane.h"

namespace accord::shape::generating
{
	class PlaneY : public generating::AbstractPlane
	{
	public:
		PlaneY(double z);

		Vec3d PlacePointOnPlane(const Vec2d& position) const;

		Vec3d GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const;
	};
}