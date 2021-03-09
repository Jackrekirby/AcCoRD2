// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord
{
	enum class Axis2D
	{
		x, y
	};

	std::string EnumToString(Axis2D axis);

	void to_json(Json& j, Axis2D axis);

	template<typename OStream>
	OStream& operator<<(OStream& os, const Axis2D& axis)
	{
		return os << EnumToString(axis);
	}
}
