#pragma once
#include "basic_cylinder.h"
#include "collision_circle.h"
#include "collision_circle_surface.h"

namespace accord
{
	struct Vec3d;
	enum class Axis3D;
}

namespace accord::shape::collision
{
	class Cylinder : public basic::Cylinder
	{
	public:
		Cylinder(const Vec3d& base_centre, double radius, double length, const Axis3D& axis);

		std::optional<Collision3D> CalculateExternalCollisionData
		(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateInternalCollisionData
		(const Vec3d& origin, const Vec3d& end) const;
	private:
		Circle circle;
		CircleSurface base_face;
		CircleSurface top_face;
	};
}