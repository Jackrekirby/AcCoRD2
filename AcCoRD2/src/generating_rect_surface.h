#pragma once
#include "generating_surface_3d.h"
#include "generating_box_2d.h"

namespace accord::shape::generating
{
	class BoxSurface3D : public Surface3D
	{
	public:
		BoxSurface3D(std::unique_ptr<AbstractPlane3D> plane, Box2D box);

		const Box2D& GetShape() const;
	private:
		Box2D box;
	};
}
