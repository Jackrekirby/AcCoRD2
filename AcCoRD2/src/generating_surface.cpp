#include "pch.h"
#include "generating_surface.h"

namespace accord::shape::generating
{

	Surface::Surface(std::unique_ptr<AbstractPlane> plane)
		: plane(std::move(plane))
	{

	}

	Vec3d Surface::GeneratePointOnSurface() const
	{
		return plane->PlacePointOnPlane(GetShape().GeneratePointInArea());
	}

	const AbstractPlane& Surface::GetPlane() const
	{
		return *plane;
	}

	void to_json(Json& j, const Surface& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
