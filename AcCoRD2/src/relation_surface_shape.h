#pragma once

namespace accord::shape::relation
{
	class Box2D;
	class Circle;

	class Surface3DShape
	{
	public:
		Surface3DShape() = default;

		virtual bool IsOverlapping(const Box2D& other) const = 0;

		virtual bool IsEnveloping(const Box2D& other) const = 0;

		virtual bool IsEnvelopedBy(const Box2D& other) const = 0;

		virtual bool IsOverlapping(const Circle& other) const = 0;

		virtual bool IsEnveloping(const Circle& other) const = 0;

		virtual bool IsEnvelopedBy(const Circle& other) const = 0;

		virtual bool IsOverlapping(const Surface3DShape& other) const = 0;

		virtual bool IsEnveloping(const Surface3DShape& other) const = 0;

		virtual bool IsEnvelopedBy(const Surface3DShape& other) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const Surface3DShape& surface_shape);
}