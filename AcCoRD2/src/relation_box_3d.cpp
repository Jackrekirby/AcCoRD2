#include "pch.h"
#include "relation_box_3d.h"
#include "relation_box_2d.h"
//#include "basic_box_3d.h"
#include "vec3b.h"

namespace accord::shape::relation
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: basic::Box3D(origin, length), faces(GenerateFaces())
	{
		
	}

	std::enum_array<Face, BoxSurface3D, 6> Box3D::GenerateFaces()
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

	BoxSurface3D Box3D::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end)
	{
		return { { origin.GetAxis(axis), axis }, { origin.GetPlane(axis), end.GetPlane(axis) } };
	}

	bool Box3D::IsOverlapping(const Box3D& other) const
	{
		return (GetOrigin() <= other.GetEnd() && GetEnd() >= other.GetOrigin()).All();
	}

	bool Box3D::IsEnveloping(const Box3D& other) const
	{
		return (GetOrigin() <= other.GetOrigin() && GetEnd() >= other.GetEnd()).All();
	}

	std::optional<Face> Box3D::IsPartiallyNeighbouring(const Box3D& other) const
	{
		for (auto& face : face_types)
		{
			if (faces.at(face).IsPartiallyNeighbouring(other.faces.at(GetOppositeFace(face)))) return face;
		}
		return std::nullopt;
	}

	std::optional<Face> Box3D::IsFullyNeighbouring(const Box3D& other) const
	{
		for (auto& face : face_types)
		{
			if (faces.at(face).IsFullyNeighbouring(other.faces.at(GetOppositeFace(face)))) return face;
		}
		return std::nullopt;
	}

	// assumes there is overlap
	Box3D Box3D::GenerateOverlapBox(const Box3D& other) const
	{
		Vec3d origin = Vec3d::Max(GetOrigin(), other.GetOrigin());
		Vec3d end = Vec3d::Min(GetEnd(), other.GetEnd());
		return { origin, end - origin };
	}

	void Box3D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box3D>(*this);
	}

	const std::enum_array<Face, BoxSurface3D, 6>& Box3D::GetFaces() const
	{
		return faces;
	}
}
