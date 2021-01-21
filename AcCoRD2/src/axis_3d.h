#pragma once
#include "pch.h"

namespace accord
{
	enum class Axis3D
	{
		x, y, z
	};

	std::string EnumToString(Axis3D axis);

	Axis3D StringToEnum(const std::string& axis);

	std::array<Axis3D, 2> GetOtherAxes(Axis3D axis);

	void to_json(Json& j, Axis3D axis);

	void from_json(const Json& j, Axis3D& axis);

	template<typename OStream>
	OStream& operator<<(OStream& os, const Axis3D& axis)
	{
		return os << EnumToString(axis);
	}
}
