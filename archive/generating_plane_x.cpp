#pragma once
#include "pch.h"
#include "generating_plane_x.h"

namespace accord::shape::generating
{
	PlaneX::PlaneX(double x)
		: AbstractPlane(x, Axis3D::x)
	{

	}

	Vec3d PlaneX::PlacePointOnPlane(const Vec2d& position) const
	{
		return { GetPosition(), position.x, position.y };
	}

	Vec3d PlaneX::GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const
	{
		return { GetPosition() + normal, tangential.x, tangential.y };
	}
}