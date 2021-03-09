// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_sphere.h"
#include "generating_shape_3d.h"

namespace accord::shape::generating
{
	class Sphere : virtual public basic::Sphere, public Shape3D
	{
	public:
		Sphere(Vec3d centre, double radius);

		Sphere(basic::Sphere sphere);

		Vec3d GeneratePointInVolume() const;

		Vec3d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}