#pragma once
#include "relation_surface.h"
#include "relation_rect.h"

namespace accord::shape::basic
{
	class RectSurface;
}

namespace accord::shape::relation
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(Plane plane, Rect rect);

		RectSurface(const basic::RectSurface& rect_surface);

		basic::RectSurface ToBasic() const;

		const Rect& GetShape() const;
	private:
		Rect rect;
	};
}
