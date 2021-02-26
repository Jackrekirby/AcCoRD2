#pragma once
#include "pch.h"
#include "relation_surface_factory.h"
#include "relation_box.h"
#include "vec3d.h"

namespace accord::shape::relation
{
	Surface3D CreateBoxSurface(double position, Axis3D axis, const Vec2d& origin, const Vec2d& end)
	{
		return { Plane3D(position, axis), std::make_unique<Box2D>(origin, end) };
	}

	Surface3D CreateBoxSurface(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end)
	{
		return CreateBoxSurface(position.GetAxis(axis), axis, origin.GetPlane(axis), end.GetPlane(axis));
	}
}