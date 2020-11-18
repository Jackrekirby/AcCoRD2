#include "pch.h"
#include "generating_surface_3d.h"

namespace accord::shape::generating
{

	Surface3D::Surface3D(std::unique_ptr<AbstractPlane3D> plane, std::unique_ptr<Surface3DShape> shape)
		: plane(std::move(plane)), shape(std::move(shape))
	{

	}

	Vec3d Surface3D::GeneratePointOnSurface() const
	{
		return plane->PlacePointOnPlane(shape->GeneratePointOnSurface());
	}

	const AbstractPlane3D& Surface3D::GetPlane() const
	{
		return *plane;
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
