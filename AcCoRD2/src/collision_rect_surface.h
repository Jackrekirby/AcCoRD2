#pragma once
#include "collision_surface.h"
#include "collision_rect.h"

namespace accord::shape::basic
{
	class RectSurface;
}

namespace accord::shape::collision
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(Plane plane, Rect rect);

		RectSurface(const basic::RectSurface& rect_surface);

		const Rect& GetShape() const;
	private:
		Rect rect;
	};
}
