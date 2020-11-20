#pragma once
#include "generating_surface.h"
#include "generating_rect.h"

namespace accord::shape::generating
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(std::unique_ptr<AbstractPlane> plane, Rect box);

		const Rect& GetShape() const;
	private:
		Rect box;
	};
}
