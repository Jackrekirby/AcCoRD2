#pragma once
#include "json.h"

namespace accord
{
	// Require Vec3d for converting position files
	struct Vec3d
	{
		double x, y, z;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Vec3d& v)
		{
			return os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		}
	};

	void to_json(Json& j, const Vec3d& v);
}