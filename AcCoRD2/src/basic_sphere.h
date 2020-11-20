#pragma once
#include "vec3d.h"

namespace accord::shape::basic
{
	class Sphere
	{
	public:
		Sphere(Vec3d centre, double radius);

		void Move(const Vec3d& centre);

		void Resize(double radius);

		const Vec3d& GetCentre() const;

		const double& GetRadius() const;

		double CalculateVolume() const;
		
		void ToJson(Json& j) const;

	private:
		Vec3d centre;
		double radius;
	};

	void to_json(Json& j, const Sphere& sphere);
}