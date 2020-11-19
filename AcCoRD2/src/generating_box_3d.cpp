#include "pch.h"
#include "generating_box_3d.h"
#include "generating_surface_3d_factory.h"

namespace accord::shape::generating
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: basic::Box3D(origin, length), faces(GenerateFaces())
	{

	}

	std::enum_array<Faces, Surface3D, 6> Box3D::GenerateFaces() const
	{
		return
		{
			CreateBoxSurface(GetOrigin(), Axis3D::x, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetOrigin(), Axis3D::y, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetOrigin(), Axis3D::z, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::x, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::y, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::z, GetOrigin(), GetEnd())
		};
	}

	Vec3d Box3D::GeneratePointOnSurface() const
	{
		return faces.at(static_cast<Faces>(Random::GenerateIntUniform(0, 5))).GeneratePointOnSurface();
	}

	void Box3D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box3D>(*this);
	}
}
