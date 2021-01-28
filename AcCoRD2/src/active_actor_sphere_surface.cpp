#include "pch.h"
#include "active_actor_sphere_surface.h"

namespace accord
{
	ActiveActorSphereSurface::ActiveActorSphereSurface(const shape::basic::Sphere& sphere)
		: shape::generating::Sphere(sphere), shape::basic::Sphere(sphere), shape::relation::Sphere(sphere)
	{
	}

	Vec3d ActiveActorSphereSurface::GenerateMolecule()
	{
		return shape::generating::Sphere::GeneratePointOnSurface();
	}

	double ActiveActorSphereSurface::CalculateVolume()
	{
		return shape::generating::Sphere::CalculateSurfaceArea();
	}

	bool ActiveActorSphereSurface::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Sphere::IsOverlapping(other);
	}

	void ActiveActorSphereSurface::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Sphere>(*this);
	}
}