#pragma once
namespace accord
{
	enum class Axis3D;
}

namespace accord::shape::relation
{
	class Box;
	class Sphere;
	class SurfaceShape;
	class Cylinder;

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

		virtual bool IsOverlapping(const Cylinder& other) const = 0;

		virtual bool IsEnveloping(const Cylinder& other) const = 0;

		virtual bool IsEnvelopedBy(const Cylinder& other) const = 0;

		virtual bool IsOverlapping(const Shape3D& other) const = 0;

		virtual bool IsEnveloping(const Shape3D& other) const = 0;

		virtual bool IsEnvelopedBy(const Shape3D& other) const = 0;

		virtual const SurfaceShape& FlattenInAxis(const Axis3D& axis) const = 0;

		virtual void ToJson(Json& j) const = 0;

		virtual const Shape3D& GetShape() const = 0;

	};

	void to_json(Json& j, const Shape3D& shape);
}