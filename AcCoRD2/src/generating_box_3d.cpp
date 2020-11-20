#include "pch.h"
#include "generating_box_3d.h"
#include "generating_surface_3d_factory.h"
#include "generating_plane_3d_factory.h"

namespace accord::shape::generating
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: basic::Box3D(origin, length), faces(GenerateFaces())
	{

	}

	std::enum_array<Face, BoxSurface3D, 6> Box3D::GenerateFaces() const
	{
		return
		{
			GenerateFace(GetOrigin(), Axis3D::x, GetOrigin(), GetEnd()),
			GenerateFace(GetOrigin(), Axis3D::y, GetOrigin(), GetEnd()),
			GenerateFace(GetOrigin(), Axis3D::z, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::x, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::y, GetOrigin(), GetEnd()),
			GenerateFace(GetEnd(), Axis3D::z, GetOrigin(), GetEnd())
		};
	}

	BoxSurface3D Box3D::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const
	{
		return { CreatePlane(position.GetAxis(axis), axis), { origin.GetPlane(axis), end.GetPlane(axis) } };
	}

	Vec3d Box3D::GeneratePointOnSurface() const
	{
		return faces.at(static_cast<Face>(Random::GenerateIntUniform(0, 5))).GeneratePointOnSurface();
	}

	void Box3D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box3D>(*this);
	}
}
