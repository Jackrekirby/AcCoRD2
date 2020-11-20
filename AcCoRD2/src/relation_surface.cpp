#include "pch.h"
#include "relation_surface_3d.h"

namespace accord::shape::relation
{

	Surface3D::Surface3D(Plane3D plane)
		: plane(plane)
	{

	}

	bool Surface3D::IsPartiallyNeighbouring(const Surface3D& other) const
	{
		return (GetPlane().IsNeighbouring(other.GetPlane()) && GetShape().IsOverlapping(other.GetShape()));
	}

	bool Surface3D::IsFullyNeighbouring(const Surface3D& other) const
	{
		return (GetPlane().IsNeighbouring(other.GetPlane()) && GetShape().IsEnveloping(other.GetShape()));
	}

	const Plane3D& Surface3D::GetPlane() const
	{
		return plane;
	}

	void to_json(Json& j, const Surface3D& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
