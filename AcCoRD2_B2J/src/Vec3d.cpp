//#include "pch.h"
#include "Vec3d.h"

namespace accord
{
	void to_json(Json& j, const Vec3d& v)
	{
		j = { v.x, v.y, v.z };
	}
}