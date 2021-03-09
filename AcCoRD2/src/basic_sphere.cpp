// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "basic_sphere.h"
#include "constants.h"

namespace accord::shape::basic
{
	Sphere::Sphere(Vec3d centre, double radius)
		: centre(centre), radius(radius), radius2(radius*radius)
	{

	}

	Box Sphere::GenerateBoundingBox() const
	{
		return *this;
	}

	void Sphere::Move(const Vec3d& centre)
	{
		this->centre = centre;
	}

	void Sphere::Resize(const double radius)
	{
		this->radius = radius;
		radius2 = radius*radius;
	}

	const Vec3d& Sphere::GetCentre() const
	{
		return centre;
	}

	const double& Sphere::GetRadius() const
	{
		return radius;
	}

	const double& Sphere::GetRadius2() const
	{
		return radius2;
	}

	double Sphere::CalculateVolume() const
	{
		return (4 / 3) * PI * std::pow(radius, 3);
	}

	double Sphere::CalculateSurfaceArea() const
	{
		return (4 * PI * radius2);
	}

	bool Sphere::IsWithinOrOnBorder(const Vec3d& position) const
	{
		return ((position - GetCentre()).Size2() < GetRadius2());
	}

	void Sphere::ToJson(Json& j) const
	{
		j = *this;
	}

	void to_json(Json& j, const Sphere& sphere)
	{
		j["type"] = "sphere";
		j["centre"] = sphere.GetCentre();
		j["radius"] = sphere.GetRadius();
	}
}