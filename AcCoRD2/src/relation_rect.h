#pragma once
#include "basic_box_2d.h"
#include "relation_surface_3d_shape.h"

namespace accord::shape::relation
{
	class Circle;

	class Box2D : public basic::Box2D, public Surface3DShape
	{
	public:
		Box2D(Vec2d origin, Vec2d length);

		bool IsOverlapping(const Box2D& other) const;

		bool IsEnveloping(const Box2D& other) const;

		bool IsEnvelopedBy(const Box2D& other) const;

		bool IsOverlapping(const Circle& other) const;

		bool IsEnveloping(const Circle& other) const;

		bool IsEnvelopedBy(const Circle& other) const;

		bool IsOverlapping(const Surface3DShape& other) const;

		bool IsEnveloping(const Surface3DShape& other) const;

		bool IsEnvelopedBy(const Surface3DShape& other) const;

		Vec2d CalculateNearestPointOnBoundary(const Vec2d& position) const;

		Vec2d CalculateFurthestCornerFromPoint(const Vec2d& position) const;

		Box2D GenerateOverlapBox(const Box2D& other) const;

		void ToJson(Json& j) const;
	};
}