#include "abstract_plane_3d.h"

namespace accord::shape::collision
{
	AbstractPlane3D::AbstractPlane3D(double position, Axis3D axis)
		: Plane(position), axis(axis)
	{

	}

	const  Axis3D& AbstractPlane3D::GetAxis() const
	{
		return axis;
	}

	void to_json(Json& j, const AbstractPlane3D& plane)
	{
		j["position"] = plane.GetPosition();
		j["axis"] = EnumToString(plane.GetAxis());
	}
}