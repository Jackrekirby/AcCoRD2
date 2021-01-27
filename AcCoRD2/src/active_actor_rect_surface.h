#pragma once
#include "active_actor_shape.h"
#include "generating_rect_surface.h"
#include "relation_rect_surface.h"

namespace accord
{
	class ActiveActorRectSurface : public ActiveActorShape, public shape::generating::RectSurface, public shape::relation::RectSurface
	{
	public:
		ActiveActorRectSurface(const shape::basic::RectSurface& rect_surface);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}