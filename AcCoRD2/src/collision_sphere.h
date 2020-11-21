#pragma once
#include "collision_3d.h"
#include "basic_sphere.h"

namespace accord::shape::collision
{
	class Sphere : public basic::Sphere
	{
	public:
		Sphere(Vec3d centre, double radius);

		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end);

		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end);

	private:

		struct CollisionTimes
		{
			double t1, t2;

			CollisionTimes(double t1, double t2);
		};

		std::optional<CollisionTimes> CalculateCollisionTime(const Vec3d& origin, const Vec3d& end);

		std::optional<double> SelectExternalCollisionTime(double t1, double t2);

		std::optional<double> SelectInternalCollisionTime(double t1, double t2);
	};

	void to_json(Json& j, const Sphere& sphere);
}
