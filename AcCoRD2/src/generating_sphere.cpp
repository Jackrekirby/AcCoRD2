#include "pch.h"
#include "generating_sphere.h"
#include "constants.h"

namespace accord::shape::generating
{
	Sphere::Sphere(Vec3d centre, double radius)
		: basic::Sphere(centre, radius), generating::Shape3D()
	{

	}

	Sphere::Sphere(basic::Sphere sphere)
		: basic::Sphere(sphere), generating::Shape3D()
	{

	}

	Vec3d Sphere::GeneratePointInVolume() const
	{
		return (GetCentre() + Vec3d::GenerateRandomPolar() * GetRadius());
	}

	Vec3d Sphere::GeneratePointOnSurface() const
	{
		return (GetCentre() + Vec3d::GenerateRandomPolar(GetRadius()));
	}

	void Sphere::ToJson(Json& j) const
	{
		j = static_cast<basic::Sphere>(*this);
	}
}
