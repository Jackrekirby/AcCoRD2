#pragma once
#include "basic_box_2d.h"

namespace accord::shape::relation
{
	class Box2D : public basic::Box2D
	{
	public:
		Box2D(Vec2d origin, Vec2d length);

		bool IsOverlapping(const Box2D& other) const;

		bool IsEnveloping(const Box2D& other) const;

		void ToJson(Json& j) const;
	};
}