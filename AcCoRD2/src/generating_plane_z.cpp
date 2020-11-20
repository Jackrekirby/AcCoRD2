#pragma once
#include "pch.h"
#include "generating_plane_z_3d.h"

namespace accord::shape::generating
{
	PlaneZ3D::PlaneZ3D(double z)
		: AbstractPlane3D(z, Axis3D::z)
	{

	}

	Vec3d PlaneZ3D::PlacePointOnPlane(const Vec2d& position) const
	{
		return { position.x, position.y, GetPosition() };
	}

	Vec3d PlaneZ3D::GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const
	{
		return { tangential.x, tangential.y, GetPosition() + normal };
	}
}