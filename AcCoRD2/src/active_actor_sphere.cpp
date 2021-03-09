// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "active_actor_sphere.h"

namespace accord
{
	ActiveActorSphere::ActiveActorSphere(const shape::basic::Sphere& sphere)
		: shape::generating::Sphere(sphere), shape::basic::Sphere(sphere), shape::relation::Sphere(sphere)
	{
	}

	Vec3d ActiveActorSphere::GenerateMolecule()
	{
		return shape::generating::Sphere::GeneratePointInVolume();
	}

	double ActiveActorSphere::CalculateVolume()
	{
		return shape::generating::Sphere::CalculateVolume();
	}

	bool ActiveActorSphere::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Sphere::IsOverlapping(other);
	}

	void ActiveActorSphere::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Sphere>(*this);
	}
}