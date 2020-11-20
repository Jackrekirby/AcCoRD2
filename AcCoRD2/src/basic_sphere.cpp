#include "pch.h"
#include "basic_sphere.h"
#include "constants.h"

namespace accord::shape::basic
{
	Sphere::Sphere(Vec3d centre, double radius)
		: centre(centre), radius(radius)
	{

	}

	void Sphere::Move(const Vec3d& centre)
	{
		this->centre = centre;
	}

	void Sphere::Resize(const double radius)
	{
		this->radius = radius;
	}

	const Vec3d& Sphere::GetCentre() const
	{
		return centre;
	}

	const double& Sphere::GetRadius() const
	{
		return radius;
	}

	double Sphere::CalculateVolume() const
	{
		return (4 / 3) * PI * std::pow(radius, 3);
	}

	void Sphere::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Sphere& sphere)
	{
		j["centre"] = sphere.GetCentre();
		j["radius"] = sphere.GetRadius();
	}
}