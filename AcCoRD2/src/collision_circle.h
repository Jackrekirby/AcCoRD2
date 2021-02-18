#pragma once
#include "collision_2d.h"
#include "basic_circle.h"
#include "collision_shape_2d.h"

namespace accord::shape::collision
{
	// collision circle handle the collision of molecules with circles, which is used by microscopic cylinder regions
	// note collision algorithm is almost identical to that of a sphere, thus any bugs found in circle collision algorithm
	// should also be fixed in sphere class, and vice versa
	class Circle : public basic::Circle, public Shape2D
	{
	public:
		// define the circle either with primitive parameters or a basic circle
		Circle(Vec2d centre, double radius);

		Circle(basic::Circle circle);

		// calculate the intersection point, time of intersection and reflected position
		// of a ray starting at 'origin' to 'end' with the OUTSIDE surface.
		// returns null if no collision occured. see Collision 3D
		std::optional<Collision2D> CalculateExternalCollisionData(const Vec2d& origin, const Vec2d& end) const;

		// calculate the intersection point, time of intersection and reflected position
		// of a ray starting at 'origin' to 'end' with the INSIDE surface.
		// returns null if no collision occured. see Collision 3D
		std::optional<Collision2D> CalculateInternalCollisionData(const Vec2d& origin, const Vec2d& end) const;

		// see basic circle
		bool IsWithinOrOnBorder(const Vec2d& position) const;

		void ToJson(Json& j) const;

	private:
		struct CollisionTimes
		{
			double t1, t2;

			CollisionTimes(double t1, double t2);
		};

		// calculates the time which a ray intersects the cirle. The case in which the ray only intersects the 
		// circle once is ignored (ray must intersect circle twice to be considered a collision).
		// time refers to the relative distance of the intersection between the origin and end position
		std::optional<CollisionTimes> CalculateCollisionTime(const Vec2d& origin, const Vec2d& end) const;

		// select the correct intersection point between the ray and circle. 
		std::optional<double> SelectExternalCollisionTime(double t1, double t2) const;

		// select the correct intersection point between the ray and circle. 
		std::optional<double> SelectInternalCollisionTime(double t1, double t2) const;
	};

	void to_json(Json& j, const Circle& circle);
}
