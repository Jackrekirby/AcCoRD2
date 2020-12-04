#include "pch.h"
#include "microscopic_box_surface.h"

namespace accord::microscopic
{
	BoxSurface::BoxSurface(Vec3d origin, Vec3d length, Type type)
		: box(origin, length), Surface(type)
	{

	}

	BoxSurfaceShape& BoxSurface::GetShape()
	{
		return box;
	}
}