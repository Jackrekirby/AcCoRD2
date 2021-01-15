#pragma once
#include "pch.h"
#include "generating_plane_z.h"

namespace accord::shape::generating
{
	PlaneZ::PlaneZ(double z)
		: AbstractPlane(z, Axis3D::z)
	{

	}

	Vec3d PlaneZ::PlacePointOnPlane(const Vec2d& position) const
	{
		return { position.x, position.y, GetPosition() };
	}

	Vec3d PlaneZ::GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const
	{
		return { tangential.x, tangential.y, GetPosition() + normal };
	}
}