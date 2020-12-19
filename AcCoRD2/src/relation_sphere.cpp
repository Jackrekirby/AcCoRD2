#include "pch.h"
#include "relation_sphere.h"
#include "vec3b.h"
#include "relation_box.h"
#include "relation_circle.h"
#include "axis_3d.h"
#include "relation_cylinder.h"

namespace accord::shape::relation
{
	Sphere::Sphere(Vec3d centre, double radius)
		: basic::Sphere(centre, radius),
		projected_shapes(GenerateProjectedShapes())
	{
		Circle c(GetCentre().GetPlane(Axis3D::x), radius);
	}

	bool Sphere::IsOverlapping(const relation::Shape3D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Sphere::IsEnveloping(const relation::Shape3D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Sphere::IsEnvelopedBy(const relation::Shape3D& other) const
	{
		return other.IsEnveloping(*this);
	}

	const Circle& Sphere::FlattenInAxis(const Axis3D& axis) const
	{
		return projected_shapes.at(axis);
	}

	bool Sphere::IsOverlapping(const Box& other) const
	{
		return IsWithinOrOnBorder(other.CalculateNearestPointOnBoundary(GetCentre()));
	}

	bool Sphere::IsEnveloping(const Box& other) const
	{
		return IsWithinOrOnBorder(other.CalculateFurthestCornerFromPoint(GetCentre()));
	}

	bool Sphere::IsEnvelopedBy(const Box& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Sphere::IsOverlapping(const Cylinder& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Sphere::IsEnveloping(const Cylinder& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Sphere::IsEnvelopedBy(const Cylinder& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Sphere::IsOverlapping(const Sphere& other) const
	{
		return ((GetCentre() - other.GetCentre()).Size() < GetRadius() + other.GetRadius());
	}

	bool Sphere::IsEnveloping(const Sphere& other) const
	{
		return ((GetCentre() - other.GetCentre()).Size() + other.GetRadius() < GetRadius());
	}

	bool Sphere::IsEnvelopedBy(const Sphere& other) const
	{
		return other.IsEnveloping(*this);
	}

	const Sphere& Sphere::GetShape() const
	{
		return *this;
	}

	void Sphere::ToJson(Json& j) const
	{
		j = static_cast<basic::Sphere>(*this);
	}

	Circle Sphere::GenerateProjectedShape(const Axis3D& axis) const
	{
		return {GetCentre().GetPlane(axis), GetRadius()};
	}

	std::enum_array<Axis3D, Circle, 3> Sphere::GenerateProjectedShapes() const
	{
		return
		{
			GenerateProjectedShape(Axis3D::x),
			GenerateProjectedShape(Axis3D::y),
			GenerateProjectedShape(Axis3D::z)
		};
	}

	void to_json(Json& j, const Sphere& shape)
	{
		shape.ToJson(j);
	}
}
