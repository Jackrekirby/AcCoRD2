// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "relation_box.h"
#include "relation_rect.h"
#include "relation_sphere.h"
#include "vec3b.h"
#include "axis_3d.h"
#include "relation_cylinder.h"
#include "basic_rect_surface.h"

namespace accord::shape::relation
{
	Box::Box(Vec3d origin, Vec3d length)
		: basic::Box(origin, length), faces(GenerateFaces()),
		projected_shapes(GenerateProjectedShapes())
	{
		
	}

	Box::Box(basic::Box box)
		: basic::Box(box.GetOrigin(), box.GetLength()), faces(GenerateFaces()),
		projected_shapes(GenerateProjectedShapes())
	{
	}

	Box::Box(const RectSurface& rect_surface)
		: basic::Box(rect_surface.ToBasic()), faces(GenerateFaces()), projected_shapes(GenerateProjectedShapes())
	{

	}

	std::enum_array<Face, RectSurface, 6> Box::GenerateFaces()
	{
		return {
			GenerateFace(GetOrigin(), Axis3D::x, GetOrigin(), GetLength()),
			GenerateFace(GetOrigin(), Axis3D::y, GetOrigin(), GetLength()),
			GenerateFace(GetOrigin(), Axis3D::z, GetOrigin(), GetLength()),
			GenerateFace(GetEnd(), Axis3D::x, GetOrigin(), GetLength()),
			GenerateFace(GetEnd(), Axis3D::y, GetOrigin(), GetLength()),
			GenerateFace(GetEnd(), Axis3D::z, GetOrigin(), GetLength())
		};
	}

	std::enum_array<Axis3D, Rect, 3> Box::GenerateProjectedShapes() const
	{
		return
		{
			GenerateProjectedShape(Axis3D::x),
			GenerateProjectedShape(Axis3D::y),
			GenerateProjectedShape(Axis3D::z)
		};
	}

	Rect Box::GenerateProjectedShape(const Axis3D& axis) const
	{
		return { GetOrigin().GetPlane(axis), GetLength().GetPlane(axis) };
	}

	RectSurface Box::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& length)
	{
		return { { position.GetAxis(axis), axis }, { origin.GetPlane(axis), length.GetPlane(axis) } };
	}

	bool Box::IsOverlapping(const Box& other) const
	{
		return (GetOrigin() <= other.GetEnd() && GetEnd() >= other.GetOrigin()).All();
	}

	bool Box::IsEnveloping(const Box& other) const
	{
		return (GetOrigin() <= other.GetOrigin() && GetEnd() >= other.GetEnd()).All();
	}

	bool Box::IsEnvelopedBy(const Box& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Box::IsOverlapping(const Sphere& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Box::IsEnveloping(const Sphere& other) const
	{
		return ((other.GetCentre() - CalculateCentre()).Abs() + other.GetRadius() < (GetLength() / 2)).All();
	}

	bool Box::IsEnvelopedBy(const Sphere& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Box::IsOverlapping(const Cylinder& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Box::IsEnveloping(const Cylinder& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Box::IsEnvelopedBy(const Cylinder& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Box::IsOverlapping(const relation::Shape3D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Box::IsEnveloping(const relation::Shape3D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Box::IsEnvelopedBy(const relation::Shape3D& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Box::IsPartiallyNeighbouring(const Box& other) const
	{
		for (auto& face : face_types)
		{
			//LOG_INFO("face = {}", face);
			//LOG_INFO("surface = {} {}", faces.at(face).GetPlane(), faces.at(face).GetShape());
			//LOG_INFO("surface = {} {}", other.faces.at(GetOppositeFace(face)).GetPlane(), other.faces.at(GetOppositeFace(face)).GetShape());
			if (faces.at(face).IsPartiallyNeighbouring(other.faces.at(GetOppositeFace(face)))) return true;
		}
		return false;
	}

	bool Box::IsFullyNeighbouring(const Box& other) const
	{
		for (auto& face : face_types)
		{
			if (faces.at(face).IsFullyNeighbouring(other.faces.at(GetOppositeFace(face)))) return true;
		}
		return false;
	}

	Vec3d Box::CalculateNearestPointOnBoundary(const Vec3d& position) const
	{
		return Vec3d::Max(GetOrigin(), Vec3d::Min(position, GetEnd()));
	}

	Vec3d Box::CalculateFurthestCornerFromPoint(const Vec3d& position) const
	{
		return (GetOrigin() + (position < CalculateCentre()) * GetLength());
	}

	const Rect& Box::FlattenInAxis(const Axis3D& axis) const
	{
		return projected_shapes.at(axis);
	}

	bool Box::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return basic::Box::IsWithinOrOnBorder(position);
	}

	double Box::CalculateAreaBetweenNeighbouringBoxes(const Box& other) const
	{
		// assumed boxes do neighbour, find axis with smallest distance between them (in case of floating point error)
		Vec3d d1 = GetOrigin() - other.GetEnd();
		Vec3d d2 = GetEnd() - other.GetOrigin();
		Axis3D a1 = d1.Abs().MinAxis();
		Axis3D a2 = d2.Abs().MinAxis();
		Axis3D axis = (std::abs(d1.GetAxis(a1)) < std::abs(d2.GetAxis(a2))) ? a1 : a2;
		
		//Axis3D axis = ((GetOrigin() == other.GetEnd()) || (GetEnd() == other.GetOrigin())).FindAxis();
		//if (axis2 != axis)
		//{
		//	LOG_INFO("box = {}, neighbouring = {}, {}, {}, {}, {}, {}, {}", *this, other, axis, axis2, d1, d2, a1, a2);
		//}
		return FlattenInAxis(axis).GenerateOverlapRect(other.FlattenInAxis(axis)).CalculateArea();
	}

	// assumes there is overlap
	Box Box::GenerateOverlapBox(const Box& other) const
	{
		Vec3d origin = Vec3d::Max(GetOrigin(), other.GetOrigin());
		Vec3d end = Vec3d::Min(GetEnd(), other.GetEnd());
		return { origin, end - origin };
	}

	void Box::ToJson(Json& j) const
	{
		j = static_cast<basic::Box>(*this);
	}

	const Box& Box::GetShape() const
	{
		return *this;
	}

	const std::enum_array<Face, RectSurface, 6>& Box::GetFaces() const
	{
		return faces;
	}

	const RectSurface& Box::GetFace(Face face) const
	{
		return faces.at(face);
	}

	void to_json(Json& j, const Box& shape)
	{
		shape.ToJson(j);
	}
}
