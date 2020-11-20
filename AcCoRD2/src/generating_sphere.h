#pragma once
#include "basic_sphere.h"
#include "generating_surface_shape.h"

namespace accord::shape::generating
{
	class Sphere : public basic::Sphere, public SurfaceShape
	{
	public:
		Sphere(Vec3d centre, double radius);

		Vec3d GeneratePointInVolume() const;

		Vec3d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	};
}