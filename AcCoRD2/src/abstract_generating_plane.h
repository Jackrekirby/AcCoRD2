#pragma once
#include "basic_plane_3d.h"
#include "vec3d.h"

namespace accord::shape::generating
{
	class AbstractPlane3D : public basic::AbstractPlane3D
	{
	public:
		AbstractPlane3D(double position, Axis3D axis);

		virtual Vec3d PlacePointOnPlane(const Vec2d& position) const = 0;

		virtual Vec3d GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const = 0;
	};

	void to_json(Json& j, const AbstractPlane3D& plane);
}