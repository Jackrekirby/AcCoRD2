#include "pch.h"
#include "relation_sphere.h"
#include "vec3b.h"
#include "relation_box.h"
#include "relation_circle.h"

namespace accord::shape::relation
{
	Sphere::Sphere(Vec3d centre, double radius)
		: basic::Sphere(centre, radius)
	{

	}

	bool Sphere::IsOverlapping(const Shape3D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Sphere::IsEnveloping(const Shape3D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Sphere::IsEnvelopedBy(const Shape3D& other) const
	{
		return other.IsEnveloping(*this);
	}

	std::unique_ptr<SurfaceShape> Sphere::FlattenInAxis(Axis3D axis) const
	{
		return std::make_unique<Circle>(GetCentre().GetPlane(axis), GetRadius());
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

	void to_json(Json& j, const Sphere& shape)
	{
		shape.ToJson(j);
	}
}
