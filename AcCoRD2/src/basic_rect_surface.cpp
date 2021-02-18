#include "pch.h"
#include "basic_rect_surface.h"
#include "vec3b.h"
#include "vec3d.h"

namespace accord::shape::basic
{	
	RectSurface::RectSurface(const Plane& plane, const Rect& rect)
		: plane(plane), rect(rect)
	{

	}

	RectSurface::RectSurface(const Vec3d& origin, const Vec3d& length)
		: plane(CreatePlane(origin, length)), rect(CreateRect(origin, length))
	{

	}

	Plane RectSurface::CreatePlane(const Vec3d& origin, const Vec3d& length) const
	{
		// find the axis with zero length
		Axis3D axis = (length == Vec3d(0)).FindAxis();
		return { origin.GetAxis(axis), axis };
	}

	Rect RectSurface::CreateRect(const Vec3d& origin, const Vec3d& length) const
	{
		// find the axis with zero length
		Axis3D axis = (length == Vec3d(0)).FindAxis();
		return { origin.GetPlane(axis), length.GetPlane(axis) };
	}
}