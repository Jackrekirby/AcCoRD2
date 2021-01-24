#include "pch.h"
#include "axis_3d.h"

namespace accord
{
	std::string EnumToString(Axis3D axis) {
		switch (axis)
		{
		case Axis3D::x:
			return "X";
		case Axis3D::y:
			return "Y";
		case Axis3D::z:
			return "Z";
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	Axis3D StringToEnum(const std::string& axis) {
		if (axis == "X")
		{
			return Axis3D::x;
		} else if (axis == "Y")
		{
			return Axis3D::y;
		} else if (axis == "Z")
		{
			return Axis3D::z;
		}
		LOG_CRITICAL("Unknown Axis3D string {}", axis);
		throw std::exception();
	}

	std::array<Axis3D, 2> GetOtherAxes(Axis3D axis)
	{
		switch (axis)
		{
		case Axis3D::x:
			return { Axis3D::y, Axis3D::z };
		case Axis3D::y:
			return { Axis3D::x, Axis3D::z };
		case Axis3D::z:
			return { Axis3D::x, Axis3D::y };
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	void to_json(Json& j, Axis3D axis)
	{
		j = EnumToString(axis);
	}

	void from_json(const Json& j, Axis3D& axis) 
	{
		axis = StringToEnum(j.get<std::string>());
	}
}
