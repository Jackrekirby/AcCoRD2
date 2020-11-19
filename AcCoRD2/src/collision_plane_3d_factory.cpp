#pragma once
#include "pch.h"
#include "collision_plane_3d_factory.h"
#include "collision_plane_x_3d.h"
#include "collision_plane_y_3d.h"
#include "collision_plane_z_3d.h"

namespace accord::shape::collision
{
	std::unique_ptr<AbstractPlane3D> CreatePlane(double position, Axis3D axis)
	{
		switch (axis)
		{
		case Axis3D::x:
			return std::make_unique<PlaneX3D>(position);
		case Axis3D::y:
			return std::make_unique<PlaneY3D>(position);
		case Axis3D::z:
			return std::make_unique<PlaneZ3D>(position);
		default:
			LOG_CRITICAL("Unknown Axis3D type");
			throw std::exception();
		}
	}
}