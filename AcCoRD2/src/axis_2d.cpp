#include "pch.h"
#include "axis_2d.h"

namespace accord
{
	std::string EnumToString(Axis2D axis) {
		switch (axis)
		{
		case Axis2D::x:
			return "x";
		case Axis2D::y:
			return "y";
		}
		LOG_CRITICAL("Unknown Axis2D type");
		throw std::exception();
	}

	void to_json(Json& j, Axis2D axis)
	{
		j = EnumToString(axis);
	}
}
