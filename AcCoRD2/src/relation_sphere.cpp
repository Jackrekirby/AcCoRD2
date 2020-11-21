#include "pch.h"
#include "relation_sphere.h"
#include "vec3b.h"
#include "relation_box.h"

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

	bool Sphere::IsOverlapping(const Box& other) const
	{
		return (other.CalculateNearestPointOnBoundary(GetCentre()) - GetCentre()).Size() < GetRadius();
	}

	bool Sphere::IsEnveloping(const Box& other) const
	{
		return (other.CalculateFurthestCornerFromPoint(GetCentre()) - GetCentre()).Size() < GetRadius();
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
