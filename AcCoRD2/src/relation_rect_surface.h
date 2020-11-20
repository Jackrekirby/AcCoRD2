#pragma once
#include "relation_surface.h"
#include "relation_rect.h"

namespace accord::shape::relation
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(Plane3D plane, Rect box);

		const Rect& GetShape() const;
	private:
		Rect box;
	};
}
