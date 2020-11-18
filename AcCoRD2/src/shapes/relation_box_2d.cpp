#include "pch.h"
#include "relation_box_2d.h"
#include "vec2b.h"

namespace accord::shape::relation
{
	Box2D::Box2D(Vec2d origin, Vec2d length)
		: basic::Box2D(origin, length)
	{

	}

	bool Box2D::IsOverlapping(const Box2D& other) const
	{
		return (GetOrigin() <= other.GetEnd() && GetEnd() >= other.GetOrigin()).All();
	}

	bool Box2D::IsEnveloping(const Box2D& other) const
	{
		return (GetOrigin() <= other.GetOrigin() && GetEnd() >= other.GetEnd()).All();
	}

	void Box2D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box2D>(*this);
	}
}
