#pragma once
//#include <string>
//#include "json.h"

#include "pch.h"

namespace accord
{
	enum class Axis3D
	{
		x, y, z
	};

	std::string EnumToString(Axis3D axis);

	void to_json(Json& j, Axis3D axis);

	template<typename OStream>
	OStream& operator<<(OStream& os, const Axis3D& axis)
	{
		return os << EnumToString(axis);
	}
}
