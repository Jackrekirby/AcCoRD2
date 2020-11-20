#pragma once
#include "relation_surface_3d.h"
#include "relation_circle.h"

namespace accord::shape::relation
{
	class BoxSurface3D : public Surface3D
	{
	public:
		BoxSurface3D(Plane3D plane, Circle circle);

		const Circle& GetShape() const;
	private:
		Circle circle;
	};
}
