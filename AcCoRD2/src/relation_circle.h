#pragma once
#include "basic_circle.h"
#include "relation_shape_2d.h"

namespace accord::shape::relation
{
	class Rect;

	class Circle : public basic::Circle, public Shape2D
	{
	public:
		Circle(Vec2d centre, double radius);

		bool IsOverlapping(const Circle& other) const;

		bool IsEnveloping(const Circle& other) const;

		bool IsEnvelopedBy(const Circle& other) const;

		bool IsOverlapping(const Rect& other) const;

		bool IsEnveloping(const Rect& other) const;

		bool IsEnvelopedBy(const Rect& other) const;

		bool IsOverlapping(const Shape2D& other) const;

		bool IsEnveloping(const Shape2D& other) const;

		bool IsEnvelopedBy(const Shape2D& other) const;

		void ToJson(Json& j) const;
	};

	void to_json(Json& j, const Circle& shape);
}