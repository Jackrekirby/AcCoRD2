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
		return (GetCentre() + Vec2d::GenerateRandomPolar() * GetRadius());
	}

	Vec2d Circle::GeneratePointOnSurface() const
	{
		return (GetCentre() + Vec2d::GenerateRandomPolar(GetRadius()));
	}

	void Circle::ToJson(Json& j) const
	{
		j = static_cast<basic::Circle>(*this);
	}
}
