#include "pch.h"
#include "relation_plane.h"

namespace accord::shape::relation
{
	Plane3D::Plane3D(double position, Axis3D axis)
		: basic::AbstractPlane(position, axis)
	{

	}

	bool Plane3D::IsNeighbouring(const Plane3D& other) const
	{
		return (GetPosition() == other.GetPosition() && GetAxis() == GetAxis());
	}

	void to_json(Json& j, const Plane3D& plane)
	{
		j = static_cast<basic::AbstractPlane>(plane);
	}
}