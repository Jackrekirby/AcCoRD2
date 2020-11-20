#pragma once
#include "pch.h"
#include "generating_plane_factory.h"
#include "generating_plane_x.h"
#include "generating_plane_y.h"
#include "generating_plane_z.h"

namespace accord::shape::generating
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