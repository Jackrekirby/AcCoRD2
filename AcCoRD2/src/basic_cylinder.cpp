#include "pch.h"
#include "basic_cylinder.h"
#include "constants.h"
#include "basic_circle_surface.h"

namespace accord::shape::basic
{
	Cylinder::Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis)
		: base_centre(base_centre), radius(radius), length(length), axis(axis),
		radius2(radius* radius), base(base_centre.GetAxis(axis)),
		circle_centre(base_centre.GetPlane(axis)), top(base + length)
	{

	}

	Cylinder::Cylinder(const CircleSurface& circle_surface)
		: base_centre(Vec3d(circle_surface.plane.GetPosition(), circle_surface.circle.GetCentre(), circle_surface.plane.GetAxis())), 
			radius(circle_surface.circle.GetRadius()), length(0), axis(circle_surface.plane.GetAxis()),
		radius2(radius* radius), base(base_centre.GetAxis(axis)),
		circle_centre(base_centre.GetPlane(axis)), top(base)
	{
	}

	Box Cylinder::GenerateBoundingBox() const
	{
		return *this;
	}

	void Cylinder::Move(Vec3d base_centre)
	{
		this->base_centre = base_centre;
		circle_centre = base_centre.GetPlane(axis);
		base = base_centre.GetAxis(axis);
		top = base + length;
	}

	void Cylinder::SetRadius(double radius)
	{
		this->radius = radius;
		radius2 = radius * radius;
	}

	void Cylinder::SetLength(double length)
	{
		this->length = length;
		top = base + length;
	}

	const Vec3d& Cylinder::GetBaseCentre() const
	{
		return base_centre;
	}

	double Cylinder::GetRadius() const
	{
		return radius;
	}

	double Cylinder::GetRadius2() const
	{
		return radius2;
	}

	double Cylinder::GetLength() const
	{
		return length;
	}

	double Cylinder::GetBase() const
	{
		return base;
	}

	double Cylinder::GetTop() const
	{
		return top;
	}

	Axis3D Cylinder::GetAxis() const
	{
		return axis;
	}

	Vec2d Cylinder::GetCircleCentre() const
	{
		return circle_centre;
	}

	double Cylinder::CalculateVolume() const
	{
		return 2 * PI * radius2 * length;
	}

	double Cylinder::CalculateSurfaceArea() const
	{
		return (2 * PI * radius * length) + (2 * PI * radius2);
	}

	bool Cylinder::IsWithinBorder(const Vec3d& position) const
	{
		return (
			((position.GetPlane(axis) - circle_centre).Size2() < GetRadius2())
			&& (position.GetAxis(axis) > base)
			&& (position.GetAxis(axis) < top)
		);
	}

	bool Cylinder::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return (
			((position.GetPlane(axis) - circle_centre).Size2() <= GetRadius2())
			&& (position.GetAxis(axis) >= base)
			&& (position.GetAxis(axis) <= top)
		);
	}

	bool Cylinder::IsOnFace(const Vec3d& position) const
	{
		return (((position.GetPlane(axis) - circle_centre).Size2() <= GetRadius2()) &&
			((position.GetAxis(axis) == base) || (position.GetAxis(axis) == top)));
	}

	void Cylinder::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Cylinder& cylinder)
	{
		j["type"] = "cylinder";
		j["base_centre"] = cylinder.GetBaseCentre();
		j["radius"] = cylinder.GetRadius();
		j["length"] = cylinder.GetLength();
		j["axis"] = EnumToString(cylinder.GetAxis());
	}
}