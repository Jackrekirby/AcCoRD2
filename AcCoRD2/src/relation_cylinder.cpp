// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "relation_cylinder.h"
#include "relation_box.h"
#include "relation_sphere.h"
#include "vec1d.h"
#include "basic_circle_surface.h"

namespace accord::shape::relation
{
	Cylinder::Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis)
		: basic::Cylinder(base_centre, radius, length, axis),
		base_face({ GetBase(), axis }, { GetCircleCentre(), radius }),
		top_face({ GetTop(), axis }, { GetCircleCentre(), radius }),
		projected_face(relation::Circle( GetCircleCentre(), radius )),
		projected_side_x(relation::Box(GenerateBoundingBox()).FlattenInAxis(GetOtherAxes(GetAxis()).at(0))),
		projected_side_y(relation::Box(GenerateBoundingBox()).FlattenInAxis(GetOtherAxes(GetAxis()).at(1)))
	{

	}

	Cylinder::Cylinder(basic::Cylinder cylinder)
		: basic::Cylinder(cylinder),
		base_face({ GetBase(), cylinder.GetAxis() }, { GetCircleCentre(), cylinder.GetRadius() }),
		top_face({ GetTop(), cylinder.GetAxis() }, { GetCircleCentre(), cylinder.GetRadius() }),
		projected_face(relation::Circle(GetCircleCentre(), cylinder.GetRadius())),
		projected_side_x(relation::Box(GenerateBoundingBox()).FlattenInAxis(GetOtherAxes(GetAxis()).at(0))),
		projected_side_y(relation::Box(GenerateBoundingBox()).FlattenInAxis(GetOtherAxes(GetAxis()).at(1)))
	{

	}

	Cylinder::Cylinder(const CircleSurface& circle_surface)
		: basic::Cylinder(circle_surface.ToBasic()),
		base_face({ GetBase(), GetAxis() }, { GetCircleCentre(), GetRadius() }),
		top_face({ GetTop(), GetAxis() }, { GetCircleCentre(), GetRadius() }),
		projected_face(relation::Circle(GetCircleCentre(), GetRadius())),
		projected_side_x(relation::Box(GenerateBoundingBox()).FlattenInAxis(GetOtherAxes(GetAxis()).at(0))),
		projected_side_y(relation::Box(GenerateBoundingBox()).FlattenInAxis(GetOtherAxes(GetAxis()).at(1)))
	{

	}

	Vec3d Cylinder::CalculateNearestPoint(const Vec3d& position) const
	{
		double longitudinal = Vec1d::Max(GetBase(), Vec1d::Min(position.GetAxis(GetAxis()), GetTop()));

		Vec2d transverse = Vec2d::Max(GetBaseCentre().GetPlane(GetAxis()) - GetRadius(),
			Vec2d::Min(position.GetPlane(GetAxis()), GetBaseCentre().GetPlane(GetAxis()) + GetRadius()));

		if (transverse.Size2() < GetRadius2())
		{
			return { longitudinal, transverse, GetAxis() };
		}
		else
		{
			return { longitudinal,
			GetCircleCentre() + (transverse - GetCircleCentre()).Normalise() * GetRadius(),
			GetAxis()
			};
		}

		
	}

	Vec3d Cylinder::CalculateFurthestPoint(const Vec3d& position) const
	{
		// find if the base or top of cylinder is furthest away from the position
		double longitudinal = GetBase() + GetLength() * 
			(Vec1d::Square(position.GetAxis(GetAxis()) - GetBase()) <
					Vec1d::Square(position.GetAxis(GetAxis()) - GetTop()));

		Vec2d transverse = Vec2d::Max(GetBaseCentre().GetPlane(GetAxis()) - GetRadius(),
			Vec2d::Min(position.GetPlane(GetAxis()), GetBaseCentre().GetPlane(GetAxis()) + GetRadius()));

		if (transverse.Size2() == 0) transverse.x = GetRadius();

		return { longitudinal,
			GetCircleCentre() - (transverse - GetCircleCentre()).Normalise() * GetRadius(),
			GetAxis()
		};
	}

	bool Cylinder::IsOverlapping(const relation::Shape3D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Cylinder::IsEnveloping(const relation::Shape3D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Cylinder::IsEnvelopedBy(const relation::Shape3D& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Cylinder::IsOverlapping(const Cylinder& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsOverlapping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsOverlapping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsOverlapping(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnveloping(const Cylinder& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnveloping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnveloping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnveloping(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnvelopedBy(const Cylinder& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnvelopedBy(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnvelopedBy(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnvelopedBy(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsOverlapping(const Box& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsOverlapping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsOverlapping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsOverlapping(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnveloping(const Box& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnveloping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnveloping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnveloping(other.FlattenInAxis(Axis3D::z))
		);
	}

	bool Cylinder::IsEnvelopedBy(const Box& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnvelopedBy(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnvelopedBy(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnvelopedBy(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsOverlapping(const Sphere& other) const
	{
		return other.IsWithinOrOnBorder(CalculateNearestPoint(other.GetCentre()));
	}

	bool Cylinder::IsEnveloping(const Sphere& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnveloping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnveloping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnveloping(other.FlattenInAxis(Axis3D::z))
		);
	}

	bool Cylinder::IsEnvelopedBy(const Sphere& other) const
	{
		return other.IsWithinOrOnBorder(CalculateFurthestPoint(other.GetCentre()));
	}

	bool Cylinder::IsPartiallyNeighbouring(const Box& other) const
	{
		switch (GetAxis())
		{
		case Axis3D::x:
			if (base_face.IsPartiallyNeighbouring(other.GetFace(Face::nx))) return true;
			return top_face.IsPartiallyNeighbouring(other.GetFace(Face::px));
		case Axis3D::y:
			if (base_face.IsPartiallyNeighbouring(other.GetFace(Face::ny))) return true;
			return top_face.IsPartiallyNeighbouring(other.GetFace(Face::py));
		case Axis3D::z:
			if (base_face.IsPartiallyNeighbouring(other.GetFace(Face::nz))) return true;
			return top_face.IsPartiallyNeighbouring(other.GetFace(Face::pz));
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	bool Cylinder::IsFullyNeighbouring(const Box& other) const
	{
		switch (GetAxis())
		{
		case Axis3D::x:
			if (base_face.IsFullyNeighbouring(other.GetFace(Face::nx))) return true;
			return top_face.IsFullyNeighbouring(other.GetFace(Face::px));
		case Axis3D::y:
			if (base_face.IsFullyNeighbouring(other.GetFace(Face::ny))) return true;
			return top_face.IsFullyNeighbouring(other.GetFace(Face::py));
		case Axis3D::z:
			if (base_face.IsFullyNeighbouring(other.GetFace(Face::nz))) return true;
			return top_face.IsFullyNeighbouring(other.GetFace(Face::pz));
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	bool Cylinder::IsPartiallyNeighbouring(const Cylinder& other) const
	{
		if (base_face.IsPartiallyNeighbouring(other.top_face)) return true;
		return top_face.IsPartiallyNeighbouring(other.top_face);
	}

	// unused
	bool Cylinder::IsFullyNeighbouring(const Cylinder& other) const
	{
		if (base_face.IsFullyNeighbouring(other.top_face)) return true;
		return top_face.IsFullyNeighbouring(other.top_face);
	}

	const Shape2D& Cylinder::FlattenInAxis(const Axis3D& axis) const
	{
		if (axis == GetAxis())
		{
			return projected_face;
		}
		else
		{
			std::array<Axis3D, 2> axes = GetOtherAxes(axis);
			if (axis == axes.at(0))
			{
				return projected_side_x;
			}
			else // if (axis == axes.at(1))
			{
				return projected_side_y;
			}
		}
	}

	bool Cylinder::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return basic::Cylinder::IsWithinOrOnBorder(position);
	}

	void Cylinder::ToJson(Json& j) const
	{
		j = static_cast<basic::Cylinder>(*this);
	}

	const Cylinder& Cylinder::GetShape() const
	{
		return *this;
	}

	void to_json(Json& j, const Cylinder& shape)
	{
		shape.ToJson(j);
	}
}
