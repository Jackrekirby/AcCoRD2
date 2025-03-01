// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord
{
	// A vector containing 3 doubles (x, y, z)
	// Used to convert position data in binary files to json format
	struct Vec3d
	{
		double x, y, z;

		// logs the vector
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec3d& v)
		{
			return os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		}
	};

	// converts a vector object into json format
	void to_json(Json& j, const Vec3d& v);
}