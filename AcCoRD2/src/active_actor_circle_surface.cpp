#include "pch.h"
#include "active_actor_circle_surface.h"
#include "relation_box.h"
#include "relation_cylinder.h"

namespace accord
{
	ActiveActorCircleSurface::ActiveActorCircleSurface(const shape::basic::CircleSurface& circle_surface)
		: shape::generating::CircleSurface(circle_surface), shape::relation::CircleSurface(circle_surface)
	{
	}

	Vec3d ActiveActorCircleSurface::GenerateMolecule()
	{
		return shape::generating::CircleSurface::GeneratePointOnSurface();
	}

	double ActiveActorCircleSurface::CalculateVolume()
	{
		return shape::generating::CircleSurface::GetShape().CalculateArea();
	}

	bool ActiveActorCircleSurface::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Cylinder(static_cast<shape::relation::CircleSurface>(*this)).IsOverlapping(other);
	}

	void ActiveActorCircleSurface::ToJson(Json& j) const
	{
		j = static_cast<shape::relation::CircleSurface>(*this);
	}
}