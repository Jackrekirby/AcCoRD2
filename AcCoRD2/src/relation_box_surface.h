#pragma once
#include "relation_surface_3d.h"
#include "relation_box_2d.h"

namespace accord::shape::relation
{
	class BoxSurface3D : public Surface3D
	{
	public:
		BoxSurface3D(Plane3D plane, Box2D box);

		const Box2D& GetShape() const;
	private:
		Box2D box;
	};
}
