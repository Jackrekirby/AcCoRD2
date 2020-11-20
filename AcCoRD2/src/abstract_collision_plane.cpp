#include "abstract_collision_plane_3d.h"

namespace accord::shape::collision
{
	AbstractPlane3D::AbstractPlane3D(double position, Axis3D axis)
		: Plane1D(position, axis)
	{

	}

	void to_json(Json& j, const AbstractPlane3D& plane)
	{
		j = static_cast<Plane1D>(plane);
	}
}