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

		std::optional<double> SelectCorrectCollisionTime(double t1, double t2);

		bool IsWithinOrOnBorder(const Vec3d& position) const;
	};

	void to_json(Json& j, const Sphere& sphere);
}
