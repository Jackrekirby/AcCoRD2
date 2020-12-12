#pragma once
#include "basic_rect.h"
#include "relation_surface_shape.h"

namespace accord::shape::relation
{
	class Circle;

	class Rect : public basic::Rect, public SurfaceShape
	{
	public:
		Rect(Vec2d origin, Vec2d length);

		bool IsOverlapping(const Rect& other) const;

		bool IsEnveloping(const Rect& other) const;

		bool IsEnvelopedBy(const Rect& other) const;

		bool IsOverlapping(const Circle& other) const;

		bool IsEnveloping(const Circle& other) const;

		bool IsEnvelopedBy(const Circle& other) const;

		bool IsOverlapping(const SurfaceShape& other) const;

		bool IsEnveloping(const SurfaceShape& other) const;

		bool IsEnvelopedBy(const SurfaceShape& other) const;

		Vec2d CalculateNearestPointOnBoundary(const Vec2d& position) const;

		Vec2d CalculateFurthestCornerFromPoint(const Vec2d& position) const;

		Rect GenerateOverlapRect(const Rect& other) const;

		void ToJson(Json& j) const;
	};

	void to_json(Json& j, const Rect& shape);
}