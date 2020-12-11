#pragma once
#include "basic_sphere.h"
#include "relation_shape_3d.h"
#include "relation_surface_shape.h"

namespace accord::shape::relation
{
	class Box;

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

		bool IsOverlapping(const Shape3D& other) const;

		bool IsEnveloping(const Shape3D& other) const;

		bool IsEnvelopedBy(const Shape3D& other) const;

		std::unique_ptr<SurfaceShape> FlattenInAxis(Axis3D axis) const;

		const Sphere& GetShape() const;

		void ToJson(Json& j) const;
	};

	void to_json(Json& j, const Sphere& shape);
}