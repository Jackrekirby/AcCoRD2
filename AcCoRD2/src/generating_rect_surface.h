#pragma once
#include "generating_surface.h"
#include "generating_rect.h"

namespace accord::shape::generating
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(Plane plane, Rect rect);

		const Rect& GetShape() const;
	private:
		Rect rect;
	};
}
