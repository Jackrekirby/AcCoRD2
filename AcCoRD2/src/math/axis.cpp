#include "pch.h"

#include "axis.h"
//#include "logger.h"


namespace accord::math
{
	std::string EnumToString(Axis3D axis) {
		switch (axis)
		{
		case Axis3D::x:
			return "x";
		case Axis3D::y:
			return "y";
		case Axis3D::z:
			return "z";
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	void to_json(Json& j, Axis3D axis)
	{
		j = EnumToString(axis);
	}
}
