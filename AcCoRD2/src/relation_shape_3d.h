#pragma once
#include "axis_3d.h"

namespace accord::shape::relation
{
	class Box;
	class Sphere;
	class SurfaceShape;

	class Shape3D
	{
	public:
		Shape3D() = default;

		virtual bool IsOverlapping(const Box& other) const = 0;

		virtual bool IsEnveloping(const Box& other) const = 0;

		virtual bool IsEnvelopedBy(const Box& other) const = 0;

		virtual bool IsOverlapping(const Sphere& other) const = 0;

		virtual bool IsEnveloping(const Sphere& other) const = 0;

		virtual bool IsEnvelopedBy(const Sphere& other) const = 0;

		virtual bool IsOverlapping(const Shape3D& other) const = 0;

		virtual bool IsEnveloping(const Shape3D& other) const = 0;

		virtual bool IsEnvelopedBy(const Shape3D& other) const = 0;

		virtual std::unique_ptr<SurfaceShape> FlattenInAxis(Axis3D axis) const = 0;

		virtual void ToJson(Json& j) const = 0;

		virtual const Shape3D& GetShape() const = 0;

	};

	void to_json(Json& j, const Shape3D& shape);
}