#include "collision_box_2d.h"
#include "vec2b.h"

namespace accord::shape::collision
{
	Box2D::Box2D(Vec2d origin, Vec2d length)
		: basic::Box2D(origin, length), Surface3DShape()
	{

	}

	bool Box2D::IsWithinBorder(const Vec2d& position) const
	{
		return ((position > GetOrigin()).All() && (position < GetEnd()).All());
	}

	bool Box2D::IsWithinOrOnBorder(const Vec2d& position) const
	{
		return ((position >= GetOrigin()).All() && (position <= GetEnd()).All());
	}

	bool Box2D::IsOnBorder(const Vec2d& position) const
	{
		return ((position == GetOrigin()) || (position == GetEnd())).All();
	}

	void Box2D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box2D>(*this);
	}
}
