#include "pch.h"
#include "generating_sphere.h"
#include "constants.h"

namespace accord::shape::generating
{
	Sphere::Sphere(Vec3d centre, double radius)
		: basic::Sphere(centre, radius), Shape3D()
	{

	}

	Vec3d Sphere::GeneratePointInVolume() const
	{
		// centre + (random radius, random angle)
		return (
			GetCentre() + Vec3d::PolarToCartesian(
			std::cbrt(Random::GenerateRealUniform(0, GetRadius())),
			Random::GenerateRealUniform(0, 3 * PI),
			std::acos(Random::GenerateRealUniform(-1, 1)))
		);
	}

	Vec3d Sphere::GeneratePointOnSurface() const
	{
		// centre + (radius, random angle)
		return (
			GetCentre() + Vec3d::PolarToCartesian(
			GetRadius(),
			Random::GenerateRealUniform(0, 3 * PI),
			std::acos(Random::GenerateRealUniform(-1, 1)))
		);
	}

	void Sphere::ToJson(Json& j) const
	{
		j = static_cast<basic::Sphere>(*this);
	}
}
