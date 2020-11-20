#pragma once
#include "pch.h"
#include "generating_plane_y_3d.h"

namespace accord::shape::generating
{
	PlaneY3D::PlaneY3D(double y)
		: AbstractPlane3D(y, Axis3D::y)
	{

	}

	Vec3d PlaneY3D::PlacePointOnPlane(const Vec2d& position) const
	{
		return { position.x, GetPosition(), position.y };
	}

	Vec3d PlaneY3D::GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const
	{
		return { tangential.x, GetPosition() + normal, tangential.y };
	}
}