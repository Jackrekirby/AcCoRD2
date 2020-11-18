#include "pch.h"
#include "basic_plane_3d.h"

namespace accord::shape::basic
{
	AbstractPlane3D::AbstractPlane3D(double position, Axis3D axis)
		: position(position), axis(axis)
	{

	}

	const  Axis3D& AbstractPlane3D::GetAxis() const
	{
		return axis;
	}

	const double& AbstractPlane3D::GetPosition() const
	{
		return position;
	}

	void to_json(Json& j, const AbstractPlane3D& plane)
	{
		j["position"] = plane.GetPosition();
		j["axis"] = EnumToString(plane.GetAxis());
	}
}