#include "pch.h"
#include "generating_box_surface_3d.h"

namespace accord::shape::generating
{
	BoxSurface3D::BoxSurface3D(std::unique_ptr<AbstractPlane3D> plane, Box2D box)
		: Surface3D(std::move(plane)), box(box)
	{

	}

	const Box2D& BoxSurface3D::GetShape() const
	{
		return box;
	}
}
