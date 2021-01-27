#include "collision_rect.h"

namespace accord::shape::collision
{
	Rect::Rect(Vec2d origin, Vec2d length)
		: basic::Rect(origin, length), Shape2D()
	{

	}

	Rect::Rect(basic::Rect rect)
		: basic::Rect(rect)
	{
	}

	bool Rect::IsWithinOrOnBorder(const Vec2d& position) const
	{
		return basic::Rect::IsWithinOrOnBorder(position);
	}

	void Rect::ToJson(Json& j) const
	{
		j = static_cast<basic::Rect>(*this);
	}
}
