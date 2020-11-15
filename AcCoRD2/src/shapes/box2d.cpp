#include "box_2d.h"
#include "math/vec2b.h"

namespace accord::shapes
{
	Box2D::Box2D(math::Vec2d origin, math::Vec2d length)
		: origin(origin), length(length), end(origin + length), Surface3DShape()
	{

	}

	void Box2D::Move(const math::Vec2d& origin)
	{
		this->origin = origin;
		this->end = origin + length;
	}

	void Box2D::Resize(const math::Vec2d& length)
	{
		this->length = length;
		this->end = origin + length;
	}

	bool Box2D::IsWithinBorder(const math::Vec2d& position) const
	{
		return ((position > origin).All() && (position < end).All());
	}

	bool Box2D::IsWithinOrOnBorder(const math::Vec2d& position) const
	{
		return ((position >= origin).All() && (position <= end).All());
	}

	bool Box2D::IsOnBorder(const math::Vec2d& position) const
	{
		return ((position == origin) || (position == end)).All();
	}
}