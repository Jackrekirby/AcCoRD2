#include "pch.h"
#include "relation_rect.h"
#include "vec2b.h"
#include "relation_circle.h"

namespace accord::shape::relation
{
	Rect::Rect(Vec2d origin, Vec2d length)
		: basic::Rect(origin, length)
	{

	}

	bool Rect::IsOverlapping(const Shape2D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Rect::IsEnveloping(const Shape2D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Rect::IsEnvelopedBy(const Shape2D& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Rect::IsOverlapping(const Rect& other) const
	{
		//LOG_INFO("a = {}, b = {}", *this, other);
		return (GetOrigin() < other.GetEnd() && GetEnd() > other.GetOrigin()).All();
	}

	bool Rect::IsEnveloping(const Rect& other) const
	{
		return (GetOrigin() <= other.GetOrigin() && GetEnd() >= other.GetEnd()).All();
	}

	bool Rect::IsEnvelopedBy(const Rect& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Rect::IsOverlapping(const Circle& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Rect::IsEnveloping(const Circle& other) const
	{
		return ((other.GetCentre() - CalculateCentre()).Abs() + other.GetRadius() < (GetLength() / 2)).All();
	}

	bool Rect::IsEnvelopedBy(const Circle& other) const
	{
		return other.IsEnveloping(*this);
	}

	Vec2d Rect::CalculateNearestPointOnBoundary(const Vec2d& position) const
	{
		return Vec2d::Max(GetOrigin(), Vec2d::Min(position, GetEnd()));
	}

	Vec2d Rect::CalculateFurthestCornerFromPoint(const Vec2d& position) const
	{
		return (GetOrigin() + (position < CalculateCentre()) * GetLength());
	}

	// assumes there is overlap
	Rect Rect::GenerateOverlapRect(const Rect& other) const
	{
		Vec2d origin = Vec2d::Max(GetOrigin(), other.GetOrigin());
		Vec2d end = Vec2d::Min(GetEnd(), other.GetEnd());
		return { origin, end - origin };
	}

	void Rect::ToJson(Json& j) const
	{
		j = static_cast<basic::Rect>(*this);
	}

	void to_json(Json& j, const Rect& shape)
	{
		shape.ToJson(j);
	}
}
