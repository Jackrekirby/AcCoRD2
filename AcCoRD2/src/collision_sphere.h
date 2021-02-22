#pragma once
#include "collision_3d.h"
#include "basic_sphere.h"
#include "collision_shape_3d.h"

namespace accord::shape::collision
{
	// collision sphere handle the collision of molecules with microscopic sphere regions
	class Sphere : virtual public basic::Sphere, public Shape3D
	{
	public:
		// define the sphere either with primitive parameters or a basic sphere
		Sphere(Vec3d centre, double radius);

		Sphere(basic::Sphere sphere);

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

		struct CollisionTimes
		{
			double t1, t2;

			CollisionTimes(double t1, double t2);
		};

		// calculates the time which a ray intersects the sphere. The case in which the ray only intersects the 
		// sphere once is ignored (ray must intersect sphere twice to be considered a collision).
		// time refers to the relative distance of the intersection between the origin and end position
		std::optional<CollisionTimes> CalculateCollisionTime(const Vec3d& origin, const Vec3d& end) const;

		// select the correct intersection point between the ray and sphere. 
		std::optional<double> SelectExternalCollisionTime(double t1, double t2) const;

		// select the correct intersection point between the ray and sphere. 
		std::optional<double> SelectInternalCollisionTime(double t1, double t2) const;
	};

	void to_json(Json& j, const Sphere& sphere);
}
