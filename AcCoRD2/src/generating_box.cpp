#include "pch.h"
#include "generating_box.h"
//#include "generating_surface_factory.h"
#include "generating_plane_factory.h"

namespace accord::shape::generating
{
	Box::Box(Vec3d origin, Vec3d length)
		: basic::Box(origin, length), faces(GenerateFaces())
	{

	}

	std::enum_array<Face, RectSurface, 6> Box::GenerateFaces() const
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

	RectSurface Box::GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const
	{
		return { CreatePlane(position.GetAxis(axis), axis), { origin.GetPlane(axis), end.GetPlane(axis) } };
	}

	Vec3d Box::GeneratePointOnSurface() const
	{
		return faces.at(static_cast<Face>(Random::GenerateIntUniform(0, 5))).GeneratePointOnSurface();
	}

	Vec3d Box::GeneratePointInVolume() const
	{
		return { 
			Random::GenerateRealUniform(GetOrigin().x, GetEnd().x),
			Random::GenerateRealUniform(GetOrigin().y, GetEnd().y),
			Random::GenerateRealUniform(GetOrigin().z, GetEnd().z)
		};
	}

	void Box::ToJson(Json& j) const
	{
		j = static_cast<basic::Box>(*this);
	}
}
