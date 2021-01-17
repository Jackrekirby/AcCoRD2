#include "pch.h"
#include "relation_surface.h"

namespace accord::shape::relation
{

	Surface::Surface(Plane plane)
		: plane(plane)
	{

	}

	bool Surface::IsPartiallyNeighbouring(const Surface& other) const
	{
		//LOG_INFO("plane = {},  {}", GetPlane().GetPosition(), other.GetPlane().GetPosition());
		return (GetPlane().IsNeighbouring(other.GetPlane()) && GetShape().IsOverlapping(other.GetShape()));
	}

	bool Surface::IsFullyNeighbouring(const Surface& other) const
	{
		return (GetPlane().IsNeighbouring(other.GetPlane()) && GetShape().IsEnveloping(other.GetShape()));
	}

	const Plane& Surface::GetPlane() const
	{
		return plane;
	}

	void to_json(Json& j, const Surface& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}
