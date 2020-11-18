#include "pch.h"
#include "relation_circle.h"
#include "vec2b.h"
#include "relation_box_2d.h"

namespace accord::shape::relation
{
	Circle::Circle(Vec2d centre, double radius)
		: basic::Circle(centre, radius)
	{

	}

	bool Circle::IsOverlapping(const Surface3DShape& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Circle::IsEnveloping(const Surface3DShape& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Circle::IsEnvelopedBy(const Surface3DShape& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Circle::IsOverlapping(const Box2D& other) const
	{
		return (other.CalculateNearestPointOnBoundary(GetCentre()) - GetCentre()).Size() < GetRadius();
	}

	bool Circle::IsEnveloping(const Box2D& other) const
	{
		return (other.CalculateFurthestCornerFromPoint(GetCentre()) - GetCentre()).Size() < GetRadius();
	}

	bool Circle::IsEnvelopedBy(const Box2D& other) const
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
}
