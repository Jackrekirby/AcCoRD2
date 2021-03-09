// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "basic_cylinder.h"
#include "generating_circle.h"
#include "generating_circle_surface.h"
#include "generating_shape_3d.h"

namespace accord::shape::generating
{
	class Cylinder : virtual public basic::Cylinder, public Shape3D
	{
	public:
		Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis);

		Cylinder(basic::Cylinder cylinder);

		Vec3d GeneratePointOnSurface() const;

		Vec3d GeneratePointInVolume() const;

		void ToJson(Json& j) const;
	private:
		CircleSurface base_face;
		CircleSurface top_face;
		Circle tube;
	};
}
