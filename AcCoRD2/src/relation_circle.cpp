#include "pch.h"
#include "relation_circle.h"
#include "vec2b.h"
#include "relation_rect.h"

namespace accord::shape::relation
{
	Circle::Circle(Vec2d centre, double radius)
		: basic::Circle(centre, radius)
	{

	}

	bool Circle::IsOverlapping(const SurfaceShape& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Circle::IsEnveloping(const SurfaceShape& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Circle::IsEnvelopedBy(const SurfaceShape& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Circle::IsOverlapping(const Rect& other) const
	{
		return (other.CalculateNearestPointOnBoundary(GetCentre()) - GetCentre()).Size() < GetRadius();
	}

	bool Circle::IsEnveloping(const Rect& other) const
	{
		return (other.CalculateFurthestCornerFromPoint(GetCentre()) - GetCentre()).Size() < GetRadius();
	}

	bool Circle::IsEnvelopedBy(const Rect& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Circle::IsOverlapping(const Circle& other) const
	{
		return ((GetCentre() - other.GetCentre()).Size() < GetRadius() + other.GetRadius());
	}

	bool Circle::IsEnveloping(const Circle& other) const
	{
		return ((GetCentre() - other.GetCentre()).Size() + other.GetRadius() < GetRadius());
	}

	bool Circle::IsEnvelopedBy(const Circle& other) const
	{
		return other.IsEnveloping(*this);
	}

	void Circle::ToJson(Json& j) const
	{
		j = static_cast<basic::Circle>(*this);
	}

	void to_json(Json& j, const Circle& shape)
	{
		shape.ToJson(j);
	}
}
