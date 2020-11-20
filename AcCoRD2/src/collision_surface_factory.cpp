#pragma once
#include "pch.h"
#include "collision_surface_factory.h"
#include "collision_plane_factory.h"
#include "collision_rect.h"

namespace accord::shape::collision
{
	Surface CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end)
	{
		return { CreatePlane(position, axis), std::make_unique<Rect>(origin, end) };
	}

	Surface CreateBoxSurface(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end)
	{
		return CreateBoxSurface(position.GetAxis(axis), axis, origin.GetPlane(axis), end.GetPlane(axis));
	}
}