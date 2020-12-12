#pragma once
#include "basic_sphere.h"
#include "relation_shape_3d.h"
#include "generating_shape_2d.h"
#include "relation_circle.h"

namespace accord::shape::relation
{
	class Box;
	class Cylinder;

	class Sphere : public basic::Sphere, public Shape3D
	{
	public:
		Sphere(Vec3d centre, double radius);

		bool IsOverlapping(const Sphere& other) const;

		bool IsEnveloping(const Sphere& other) const;

		bool IsEnvelopedBy(const Sphere& other) const;

		bool IsOverlapping(const Box& other) const;

		bool IsEnveloping(const Box& other) const;

		bool IsEnvelopedBy(const Box& other) const;

		bool IsOverlapping(const Cylinder& other) const;

		bool IsEnveloping(const Cylinder& other) const;

		bool IsEnvelopedBy(const Cylinder& other) const;

		bool IsOverlapping(const Shape3D& other) const;

		bool IsEnveloping(const Shape3D& other) const;

		bool IsEnvelopedBy(const Shape3D& other) const;

		const Circle& FlattenInAxis(const Axis3D& axis) const;

		const Sphere& GetShape() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Axis3D, Circle, 3> projected_shapes;

		Circle GenerateProjectedShape(const Axis3D& axis) const;

		std::enum_array<Axis3D, Circle, 3> GenerateProjectedShapes() const;
	};

	void to_json(Json& j, const Sphere& shape);
}