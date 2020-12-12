#include "pch.h"
#include "relation_plane.h"

namespace accord::shape::relation
{
	Plane::Plane(double position, Axis3D axis)
		: basic::Plane(position, axis)
	{

	}

	bool Plane::IsNeighbouring(const Plane& other) const
	{
		return (GetPosition() == other.GetPosition() && GetAxis() == GetAxis());
	}

	void to_json(Json& j, const Plane& plane)
	{
		j = static_cast<basic::Plane>(plane);
	}
}