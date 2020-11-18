#include "pch.h"
#include "abstract_generating_plane_3d.h"

namespace accord::shape::generating
{
	AbstractPlane3D::AbstractPlane3D(double position, Axis3D axis)
		: basic::AbstractPlane3D(position, axis)
	{

	}

	void to_json(Json& j, const AbstractPlane3D& plane)
	{
		j = static_cast<basic::AbstractPlane3D>(plane);
	}
}