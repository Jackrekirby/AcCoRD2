#include "abstract_collision_plane.h"

namespace accord::shape::collision
{
	AbstractPlane::AbstractPlane(double position, Axis3D axis)
		: basic::AbstractPlane(position, axis)
	{

	}

	const double& AbstractPlane::GetPosition() const
	{
		return basic::AbstractPlane::GetPosition();
	}

	void to_json(Json& j, const AbstractPlane& plane)
	{
		j = static_cast<basic::AbstractPlane>(plane);
	}

	
}