#pragma once

namespace accord::shape::relation
{
	class Rect;
	class Circle;

	class SurfaceShape
	{
	public:
		SurfaceShape() = default;

		virtual bool IsOverlapping(const Rect& other) const = 0;

		virtual bool IsEnveloping(const Rect& other) const = 0;

		virtual bool IsEnvelopedBy(const Rect& other) const = 0;

		virtual bool IsOverlapping(const Circle& other) const = 0;

		virtual bool IsEnveloping(const Circle& other) const = 0;

		virtual bool IsEnvelopedBy(const Circle& other) const = 0;

		virtual bool IsOverlapping(const SurfaceShape& other) const = 0;

		virtual bool IsEnveloping(const SurfaceShape& other) const = 0;

		virtual bool IsEnvelopedBy(const SurfaceShape& other) const = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	void to_json(Json& j, const SurfaceShape& surface_shape);
}