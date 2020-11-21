#pragma once
#include "collision_surface.h"
#include "collision_rect.h"

namespace accord::shape::collision
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(std::unique_ptr<AbstractPlane> plane, Rect rect);

		const Rect& GetShape() const;
	private:
		Rect rect;
	};
}
