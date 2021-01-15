#pragma once
#include "pch.h"
#include "collision_plane_factory.h"
#include "collision_plane_x.h"
#include "collision_plane_y.h"
#include "collision_plane_z.h"

namespace accord::shape::collision
{
	std::unique_ptr<AbstractPlane> CreatePlane(double position, Axis3D axis)
	{
		switch (axis)
		{
		case Axis3D::x:
			return std::make_unique<PlaneX>(position);
		case Axis3D::y:
			return std::make_unique<PlaneY>(position);
		case Axis3D::z:
			return std::make_unique<PlaneZ>(position);
		default:
			LOG_CRITICAL("Unknown Axis3D type");
			throw std::exception();
		}
	}
}