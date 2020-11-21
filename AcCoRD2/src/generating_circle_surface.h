#pragma once
#include "generating_surface.h"
#include "generating_circle.h"

namespace accord::shape::generating
{
	class CircleSurface : public Surface
	{
	public:
		CircleSurface(std::unique_ptr<AbstractPlane> plane, Circle circle);

		const Circle& GetShape() const;
	private:
		Circle circle;
	};
}
