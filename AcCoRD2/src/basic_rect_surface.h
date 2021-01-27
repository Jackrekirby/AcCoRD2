#pragma once
#include "basic_plane.h"
#include "basic_rect.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::shape::basic
{
	class RectSurface
	{
	public:
		RectSurface(const Plane& plane, const Rect& rect);

		RectSurface(const Vec3d& origin, const Vec3d& length);

		Plane plane;
		Rect rect;
	private:
		Plane CreatePlane(const Vec3d& origin, const Vec3d& length) const;
		Rect CreateRect(const Vec3d& origin, const Vec3d& length) const;
	};
}