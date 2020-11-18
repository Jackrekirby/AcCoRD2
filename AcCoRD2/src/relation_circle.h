#pragma once
#include "basic_circle.h"
#include "relation_surface_3d_shape.h"

namespace accord::shape::relation
{
	class Box2D;

	class Circle : public basic::Circle, public Surface3DShape
	{
	public:
		Circle(Vec2d centre, double radius);

		bool IsOverlapping(const Circle& other) const;

		bool IsEnveloping(const Circle& other) const;

		bool IsEnvelopedBy(const Circle& other) const;

		bool IsOverlapping(const Box2D& other) const;

		bool IsEnveloping(const Box2D& other) const;

		bool IsEnvelopedBy(const Box2D& other) const;

		bool IsOverlapping(const Surface3DShape& other) const;

		bool IsEnveloping(const Surface3DShape& other) const;

		bool IsEnvelopedBy(const Surface3DShape& other) const;

		void ToJson(Json& j) const;
	};
}