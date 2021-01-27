#include "pch.h"
#include "active_actor_rect_surface.h"
#include "relation_box.h"

namespace accord
{
	ActiveActorRectSurface::ActiveActorRectSurface(const shape::basic::RectSurface& rect_surface)
		: shape::generating::RectSurface(rect_surface), shape::relation::RectSurface(rect_surface)
	{
	}

	Vec3d ActiveActorRectSurface::GenerateMolecule()
	{
		return shape::generating::RectSurface::GeneratePointOnSurface();
	}

	double ActiveActorRectSurface::CalculateVolume()
	{
		return shape::generating::RectSurface::GetShape().CalculateArea();
	}

	bool ActiveActorRectSurface::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Box(static_cast<shape::relation::RectSurface>(*this)).IsOverlapping(other);
	}

	void ActiveActorRectSurface::ToJson(Json& j) const
	{
		j = static_cast<shape::relation::RectSurface>(*this);
	}
}