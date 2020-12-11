#pragma once
#include "pch.h"
#include "basic_cylinder.h"
#include "generating_circle.h"
#include "generating_circle_surface.h"

namespace accord::shape::generating
{
	class Cylinder : public basic::Cylinder
	{
	public:
		Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis);

		Vec3d GeneratePointOnSurface() const;

		Vec3d GeneratePointInVolume() const;

		void ToJson(Json& j) const;
	private:
		CircleSurface base_face;
		CircleSurface top_face;
		Circle tube;
	};
}
