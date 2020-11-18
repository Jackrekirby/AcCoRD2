#pragma once
#include "pch.h"
#include "generating_plane_x_3d.h"

namespace accord::shape::generating
{
	PlaneX3D::PlaneX3D(double x)
		: AbstractPlane3D(x, Axis3D::x)
	{

	}

	Vec3d PlaneX3D::PlacePointOnPlane(const Vec2d& position) const
	{
		return { GetPosition(), position.x, position.y };
	}
}