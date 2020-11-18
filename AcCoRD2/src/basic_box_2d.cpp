#include "pch.h"
#include "basic_box_2d.h"
#include "vec2b.h"

namespace accord::shape::basic
{
	Box2D::Box2D(Vec2d origin, Vec2d length)
		: origin(origin), length(length), end(origin + length)
	{

	}

	void Box2D::Move(const Vec2d& origin)
	{
		this->origin = origin;
		this->end = origin + length;
	}

	void Box2D::Resize(const Vec2d& length)
	{
		this->length = length;
		this->end = origin + length;
	}

	const Vec2d& Box2D::GetOrigin() const
	{
		return origin;
	}

	const Vec2d& Box2D::GetEnd() const
	{
		return end;
	}

	const Vec2d& Box2D::GetLength() const
	{
		return length;
	}
	
	void Box2D::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Box2D& box)
	{
		j["origin"] = box.GetOrigin();
		j["length"] = box.GetLength();
		j["end"] = box.GetEnd();
	}
}