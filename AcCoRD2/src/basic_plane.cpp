#include "pch.h"
#include "basic_plane.h"

namespace accord::shape::basic
{
	AbstractPlane::AbstractPlane(double position, Axis3D axis)
		: position(position), axis(axis)
	{

	}

	const  Axis3D& AbstractPlane::GetAxis() const
	{
		return axis;
	}

	const double& AbstractPlane::GetPosition() const
	{
		return position;
	}

	void to_json(Json& j, const AbstractPlane& plane)
	{
		j["position"] = plane.GetPosition();
		j["axis"] = EnumToString(plane.GetAxis());
	}
}