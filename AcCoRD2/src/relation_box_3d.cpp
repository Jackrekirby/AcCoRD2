#include "pch.h"
#include "relation_box_3d.h"
#include "relation_box_2d.h"
#include "relation_surface_3d_factory.h"
//#include "basic_box_3d.h"
#include "vec3b.h"

namespace accord::shape::relation
{
	Box3D::Box3D(Vec3d origin, Vec3d length)
		: basic::Box3D(origin, length), faces(GenerateFaces())
	{
		
	}

	std::enum_array<Faces, Surface3D, 6> Box3D::GenerateFaces()
	{
		return {
			CreateBoxSurface(GetOrigin(), Axis3D::x, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetOrigin(), Axis3D::y, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetOrigin(), Axis3D::z, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::x, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::y, GetOrigin(), GetEnd()),
			CreateBoxSurface(GetEnd(), Axis3D::z, GetOrigin(), GetEnd())
		};
	}

	bool Box3D::IsOverlapping(const Box3D& other) const
	{
		return (GetOrigin() <= other.GetEnd() && GetEnd() >= other.GetOrigin()).All();
	}

	bool Box3D::IsEnveloping(const Box3D& other) const
	{
		return (GetOrigin() <= other.GetOrigin() && GetEnd() >= other.GetEnd()).All();
	}

	bool Box3D::IsPartiallyNeighbouring(const Box3D& other) const
	{
		if (faces.at(Faces::nx).IsPartiallyNeighbouring(other.faces.at(Faces::px))) return true;
		if (faces.at(Faces::ny).IsPartiallyNeighbouring(other.faces.at(Faces::py))) return true;
		if (faces.at(Faces::nz).IsPartiallyNeighbouring(other.faces.at(Faces::pz))) return true;
		if (faces.at(Faces::px).IsPartiallyNeighbouring(other.faces.at(Faces::nx))) return true;
		if (faces.at(Faces::py).IsPartiallyNeighbouring(other.faces.at(Faces::ny))) return true;
		return faces.at(Faces::pz).IsPartiallyNeighbouring(other.faces.at(Faces::nz));
	}

	bool Box3D::IsFullyNeighbouring(const Box3D& other) const
	{
		if (faces.at(Faces::nx).IsFullyNeighbouring(other.faces.at(Faces::px))) return true;
		if (faces.at(Faces::ny).IsFullyNeighbouring(other.faces.at(Faces::py))) return true;
		if (faces.at(Faces::nz).IsFullyNeighbouring(other.faces.at(Faces::pz))) return true;
		if (faces.at(Faces::px).IsFullyNeighbouring(other.faces.at(Faces::nx))) return true;
		if (faces.at(Faces::py).IsFullyNeighbouring(other.faces.at(Faces::ny))) return true;
		return faces.at(Faces::pz).IsFullyNeighbouring(other.faces.at(Faces::nz));
	}

	void Box3D::ToJson(Json& j) const
	{
		j = static_cast<basic::Box3D>(*this);
	}

	const std::enum_array<Faces, Surface3D, 6>& Box3D::GetFaces() const
	{
		return faces;
	}
}
