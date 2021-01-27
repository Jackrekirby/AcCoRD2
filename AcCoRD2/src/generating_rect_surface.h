#pragma once
#include "generating_surface.h"
#include "generating_rect.h"

namespace accord::shape::basic
{
	class RectSurface;
}

namespace accord::shape::generating
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
