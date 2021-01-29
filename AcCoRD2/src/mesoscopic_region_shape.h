#pragma once
#include "microscopic_box_surface_shape.h"
#include "relation_box.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::mesoscopic
{
	class RegionShape : public microscopic::BoxSurfaceShape, public shape::relation::Box
	{
	public:
		RegionShape(const Vec3d& origin, const Vec3d& length)
			: BoxSurfaceShape(origin, length), shape::relation::Box(origin, length), shape::basic::Box(origin, length)
		{

		}

		void ToJson(Json& j) const
		{
			j = static_cast<shape::basic::Box>(*this);
		}
	};
}
