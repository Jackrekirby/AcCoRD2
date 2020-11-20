#pragma once
#include "pch.h"
#include "generating_plane_y.h"

namespace accord::shape::generating
{
	PlaneY::PlaneY(double y)
		: AbstractPlane(y, Axis3D::y)
	{

	}

	Vec3d PlaneY::PlacePointOnPlane(const Vec2d& position) const
	{
		return { position.x, GetPosition(), position.y };
	}

	Vec3d PlaneY::GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const
	{
		return { tangential.x, GetPosition() + normal, tangential.y };
	}
}