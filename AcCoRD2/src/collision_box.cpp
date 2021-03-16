// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "collision_box.h"
#include "collision_rect_surface.h"

namespace accord::shape::collision
{
	Box::Box(Vec3d origin, Vec3d length)
		: basic::Box(origin, length), faces(GenerateFaces())
	{

	}

	Box::Box(basic::Box box)
		: basic::Box(box), faces(GenerateFaces())
	{
	}

	std::enum_array<Face, RectSurface, 6> Box::GenerateFaces() const
	{
		return
		{
			GenerateFace(GetOrigin(), Axis3D::x, GetOrigin(), GetLength()),
			GenerateFace(GetOrigin(), Axis3D::y, GetOrigin(), GetLength()),
			GenerateFace(GetOrigin(), Axis3D::z, GetOrigin(), GetLength()),
			GenerateFace(GetEnd(), Axis3D::x, GetOrigin(), GetLength()),
			GenerateFace(GetEnd(), Axis3D::y, GetOrigin(), GetLength()),
			GenerateFace(GetEnd(), Axis3D::z, GetOrigin(), GetLength())
		};
	}

	RectSurface Box::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& length) const
	{
		return { {position.GetAxis(axis), axis}, { origin.GetPlane(axis), length.GetPlane(axis) } };
	}

	std::optional<Collision3D> Box::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		std::optional<Collision3D> collision;
		collision = faces.at(Face::nx).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::ny).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::nz).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::px).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::py).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::pz).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { }
		return collision;
	}

	std::optional<Collision3D> Box::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		std::optional<Collision3D> collision;
		collision = faces.at(Face::nx).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::ny).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::nz).CalculateCollisionDataWithPositiveFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::px).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::py).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { return collision; }
		collision = faces.at(Face::pz).CalculateCollisionDataWithNegativeFace(origin, end);
		if (collision.has_value()) { }
		return collision;
	}

	const std::enum_array<Face, RectSurface, 6>& Box::GetFaces() const
	{
		return faces;
	}

	void Box::ToJson(Json& j) const
	{
		j = static_cast<basic::Box>(*this);
		j["faces"] = GetFaces();
	}

	void to_json(Json& j, const Box& box)
	{
		box.ToJson(j);
	}
}