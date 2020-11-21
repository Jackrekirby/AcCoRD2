#pragma once
#include "basic_circle.h"
#include "relation_surface_shape.h"

namespace accord::shape::relation
{
	class Rect;

	class Circle : public basic::Circle, public SurfaceShape
	{
	public:
		Circle(Vec2d centre, double radius);

		bool IsOverlapping(const Circle& other) const;

		bool IsEnveloping(const Circle& other) const;

		bool IsEnvelopedBy(const Circle& other) const;

		bool IsOverlapping(const Rect& other) const;

		bool IsEnveloping(const Rect& other) const;

		bool IsEnvelopedBy(const Rect& other) const;

		bool IsOverlapping(const SurfaceShape& other) const;

		bool IsEnveloping(const SurfaceShape& other) const;

		bool IsEnvelopedBy(const SurfaceShape& other) const;

		void ToJson(Json& j) const;
	};

	void to_json(Json& j, const Circle& shape);
}