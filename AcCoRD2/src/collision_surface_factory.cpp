#pragma once
#include "pch.h"
#include "collision_surface_3d_factory.h"
#include "collision_plane_3d_factory.h"
#include "collision_box_2d.h"

namespace accord::shape::collision
{
	Surface3D CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end)
	{
		return { CreatePlane(position, axis), std::make_unique<Box2D>(origin, end) };
	}

	Surface3D CreateBoxSurface(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end)
	{
		return CreateBoxSurface(position.GetAxis(axis), axis, origin.GetPlane(axis), end.GetPlane(axis));
	}
}