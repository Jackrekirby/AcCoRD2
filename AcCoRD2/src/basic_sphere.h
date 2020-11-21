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

		const double& GetRadius2() const;

		double CalculateVolume() const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;
		
		void ToJson(Json& j) const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Sphere& sphere)
		{
			return os << fmt::format("centre = {}, radius = {}",
				sphere.GetCentre(), sphere.GetRadius());
		}
	private:
		Vec3d centre;
		double radius;
		double radius2;
	};

	void to_json(Json& j, const Sphere& sphere);
}