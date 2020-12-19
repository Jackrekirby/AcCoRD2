#include "pch.h"
#include "basic_plane.h"

namespace accord::shape::basic
{
	Plane::Plane(double position, Axis3D axis)
		: position(position), axis(axis)
	{

	}

	const  Axis3D& Plane::GetAxis() const
	{
		return axis;
	}

	const double& Plane::GetPosition() const
	{
		return position;
	}

	void Plane::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Plane& plane)
	{
		j["type"] = "plane";
		j["position"] = plane.GetPosition();
		j["axis"] = EnumToString(plane.GetAxis());
	}
}