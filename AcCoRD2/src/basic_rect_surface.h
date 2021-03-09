// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

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
		// a rectangle in 3D space, defined by a plane and a rectangle which lies on the plane
		RectSurface(const Plane& plane, const Rect& rect);

		// construct rectangular surface from its negative most vertex and its length along each dimension
		// exactly 2 of the dimensions should have non-zero length, and 1 dimension with a zero length
		// will throw error if length has been specified incorrectly
		RectSurface(const Vec3d& origin, const Vec3d& length);

		Plane plane;
		Rect rect;
	private:
		Plane CreatePlane(const Vec3d& origin, const Vec3d& length) const;
		Rect CreateRect(const Vec3d& origin, const Vec3d& length) const;
	};
}