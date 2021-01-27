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

	Circle::Circle(basic::Circle circle)
		: basic::Circle(circle)
	{

	}

	bool Circle::IsOverlapping(const Shape2D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Circle::IsEnveloping(const Shape2D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Circle::IsEnvelopedBy(const Shape2D& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Circle::IsOverlapping(const Rect& other) const
	{
		return IsWithinOrOnBorder(other.CalculateNearestPointOnBoundary(GetCentre()));
	}

	bool Circle::IsEnveloping(const Rect& other) const
	{
		return IsWithinOrOnBorder(other.CalculateFurthestCornerFromPoint(GetCentre()));
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
