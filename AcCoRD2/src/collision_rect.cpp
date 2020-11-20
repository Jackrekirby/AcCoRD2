#include "collision_rect.h"
#include "vec2b.h"

namespace accord::shape::collision
{
	Rect::Rect(Vec2d origin, Vec2d length)
		: basic::Rect(origin, length), SurfaceShape()
	{

	}

	bool Rect::IsWithinBorder(const Vec2d& position) const
	{
		return ((position > GetOrigin()).All() && (position < GetEnd()).All());
	}

	bool Rect::IsWithinOrOnBorder(const Vec2d& position) const
	{
		return ((position >= GetOrigin()).All() && (position <= GetEnd()).All());
	}

	bool Rect::IsOnBorder(const Vec2d& position) const
	{
		return ((position == GetOrigin()) || (position == GetEnd())).All();
	}

	void Rect::ToJson(Json& j) const
	{
		j = static_cast<basic::Rect>(*this);
	}
}
