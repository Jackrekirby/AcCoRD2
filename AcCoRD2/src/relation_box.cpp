#include "pch.h"
#include "relation_box.h"
#include "relation_box.h"
//#include "basic_box.h"
#include "vec3b.h"

namespace accord::shape::relation
{
	Box::Box(Vec3d origin, Vec3d length)
		: basic::Box(origin, length), faces(GenerateFaces())
	{
		
	}

	std::enum_array<Face, RectSurface, 6> Box::GenerateFaces()
	{
		return {
			GenerateFace(GetOrigin(), Axis3D::x, GetOrigin(), GetEnd()),
			GenerateFace(GetOrigin(), Axis3D::y, GetOrigin(), GetEnd()),
			GenerateFace(GetOrigin(), Axis3D::z, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::x, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::y, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::z, GetOrigin(), GetEnd())
		};
	}

	RectSurface Box::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end)
	{
		return { { origin.GetAxis(axis), axis }, { origin.GetPlane(axis), end.GetPlane(axis) } };
	}

	bool Box::IsOverlapping(const Box& other) const
	{
		return (GetOrigin() <= other.GetEnd() && GetEnd() >= other.GetOrigin()).All();
	}

	bool Box::IsEnveloping(const Box& other) const
	{
		return (GetOrigin() <= other.GetOrigin() && GetEnd() >= other.GetEnd()).All();
	}

	std::optional<Face> Box::IsPartiallyNeighbouring(const Box& other) const
	{
		for (auto& face : face_types)
		{
			if (faces.at(face).IsPartiallyNeighbouring(other.faces.at(GetOppositeFace(face)))) return face;
		}
		return std::nullopt;
	}

	std::optional<Face> Box::IsFullyNeighbouring(const Box& other) const
	{
		for (auto& face : face_types)
		{
			if (faces.at(face).IsFullyNeighbouring(other.faces.at(GetOppositeFace(face)))) return face;
		}
		return std::nullopt;
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

	const std::enum_array<Face, RectSurface, 6>& Box::GetFaces() const
	{
		return faces;
	}
}
