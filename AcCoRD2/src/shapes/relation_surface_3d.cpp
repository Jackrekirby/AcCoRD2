#include "pch.h"
#include "relation_surface_3d.h"

namespace accord::shape::relation
{

	Surface3D::Surface3D(Plane3D plane, std::unique_ptr<Surface3DShape> shape)
		: plane(plane), shape(std::move(shape))
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

	const Surface3DShape& Surface3D::GetShape() const
	{
		return *shape;
	}

	void to_json(Json& j, const Surface3D& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
