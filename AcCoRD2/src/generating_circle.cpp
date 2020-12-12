#include "pch.h"
#include "generating_circle.h"
#include "constants.h"

namespace accord::shape::generating
{
	Circle::Circle(Vec2d centre, double radius)
		: basic::Circle(centre, radius), Shape2D()
	{

	}

	Vec2d Circle::GeneratePointInArea() const
	{
		// centre + (random radius, random angle)
		return GetCentre() + Vec2d::PolarToCartesian(
			std::sqrt(Random::GenerateRealUniform(0, GetRadius())),
			Random::GenerateRealUniform(0, 2 * PI)
		);
	}

	Vec2d Circle::GeneratePointOnSurface() const
	{
		// centre + (radius, random angle)
		return GetCentre() + Vec2d::PolarToCartesian(
			GetRadius(),
			Random::GenerateRealUniform(0, 2 * PI)
		);
	}

	void Circle::ToJson(Json& j) const
	{
		j = static_cast<basic::Circle>(*this);
	}
}
