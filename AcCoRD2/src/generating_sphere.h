#pragma once
#include "basic_sphere.h"
#include "generating_surface_3d_shape.h"

namespace accord::shape::generating
{
	class Sphere : public basic::Sphere, public Surface3DShape
	{
	public:
		Sphere(Vec3d centre, double radius);

		Vec3d GeneratePointInVolume() const;

		Vec3d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}