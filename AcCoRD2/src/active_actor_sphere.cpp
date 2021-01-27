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