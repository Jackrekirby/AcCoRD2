#include "pch.h"
#include "generating_surface_3d.h"

namespace accord::shape::generating
{

	Surface3D::Surface3D(std::unique_ptr<AbstractPlane3D> plane)
		: plane(std::move(plane))
	{

	}

	Vec3d Surface3D::GeneratePointOnSurface() const
	{
		return plane->PlacePointOnPlane(GetShape().GeneratePointOnSurface());
	}

	const AbstractPlane3D& Surface3D::GetPlane() const
	{
		return *plane;
	}

	void to_json(Json& j, const Surface3D& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
