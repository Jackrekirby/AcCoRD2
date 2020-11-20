#pragma once
#include "basic_plane.h"
#include "vec3d.h"

namespace accord::shape::generating
{
	class AbstractPlane : public basic::AbstractPlane
	{
	public:
		AbstractPlane(double position, Axis3D axis);

		virtual Vec3d PlacePointOnPlane(const Vec2d& position) const = 0;

		virtual Vec3d GeneratePointNormalToPlane(double normal, const Vec2d& tangential) const = 0;
	};

	void to_json(Json& j, const AbstractPlane& plane);
}