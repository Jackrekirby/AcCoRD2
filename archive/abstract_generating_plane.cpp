#include "pch.h"
#include "abstract_generating_plane.h"

namespace accord::shape::generating
{
	AbstractPlane::AbstractPlane(double position, Axis3D axis)
		: basic::AbstractPlane(position, axis)
	{

	}

	void to_json(Json& j, const AbstractPlane& plane)
	{
		j = static_cast<basic::AbstractPlane>(plane);
	}
}