#include "abstract_plane_3d.h"

namespace accord::shapes
{
	AbstractPlane3D::AbstractPlane3D(double position, math::Axis3D axis)
		: Plane(position), axis(axis)
	{

	}

	const  math::Axis3D& AbstractPlane3D::GetAxis() const
	{
		return axis;
	}

	void to_json(Json& j, const AbstractPlane3D& plane)
	{
		j["position"] = plane.GetPosition();
		j["axis"] = math::EnumToString(plane.GetAxis());
	}
}