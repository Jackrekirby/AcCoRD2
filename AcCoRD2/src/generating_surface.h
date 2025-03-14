// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "vec3d.h"
#include "generating_plane.h"
#include "generating_shape_2d.h"

namespace accord::shape::generating
{
	class Surface
	{
	public:
		Surface(Plane plane);

		Vec3d GeneratePointOnSurface() const;

		const Plane GetPlane() const;

		virtual const Shape2D& GetShape() const = 0;

	private:
		Plane plane;
	};

	void to_json(Json& j, const Shape2D& surface_shape);
}
