// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_plane.h"
#include "vec3d.h"

namespace accord::shape::generating
{
	class Plane : public basic::Plane
	{
	public:
		Plane(double position, const Axis3D& axis);

		Plane(basic::Plane plane);

		Vec3d PlacePointOnPlane(const Vec2d& position) const;

		Vec3d GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const;
	};

	void to_json(Json& j, const Plane& plane);
}