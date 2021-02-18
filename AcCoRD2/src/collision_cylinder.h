#pragma once
#include "basic_cylinder.h"
#include "collision_circle.h"
#include "collision_circle_surface.h"
#include "collision_shape_3d.h"

namespace accord
{
	struct Vec3d;
	enum class Axis3D;
}

namespace accord::shape::collision
{
	class Cylinder : virtual public basic::Cylinder, public Shape3D
	{
	public:
		// define the cylinder either with primitive parameters or a basic cylinder
		Cylinder(const Vec3d& base_centre, double radius, double length, const Axis3D& axis);

		Cylinder(basic::Cylinder cylinder);

		// calculate the intersection point, time of intersection and reflected position
		// of a ray starting at 'origin' to 'end' with the OUTSIDE surface.
		// returns null if no collision occured. see Collision 3D
		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		// calculate the intersection point, time of intersection and reflected position
		// of a ray starting at 'origin' to 'end' with the INSIDE surface.
		// returns null if no collision occured. see Collision 3D
		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		void ToJson(Json& j) const;
	private:
		Circle circle;
		CircleSurface base_face;
		CircleSurface top_face;
	};

	void to_json(Json& j, const Cylinder& cylinder);
}