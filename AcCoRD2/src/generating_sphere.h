#pragma once
#include "basic_sphere.h"
#include "generating_shape_3d.h"

namespace accord::shape::generating
{
	class Sphere : public basic::Sphere, public Shape3D
	{
	public:
		Sphere(Vec3d centre, double radius);

		Vec3d GeneratePointInVolume() const;

		Vec3d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}