#pragma once
#include "relation_surface.h"
#include "relation_circle.h"

namespace accord::shape::relation
{
	class RectSurface : public Surface
	{
	public:
		RectSurface(Plane3D plane, Circle circle);

		const Circle& GetShape() const;
	private:
		Circle circle;
	};
}
