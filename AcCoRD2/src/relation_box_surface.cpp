#include "pch.h"
#include "relation_box_surface_3d.h"

namespace accord::shape::relation
{
	BoxSurface3D::BoxSurface3D(Plane3D plane, Box2D box)
		: Surface3D(plane), box(box)
	{

	}

	const Box2D& BoxSurface3D::GetShape() const
	{
		return box;
	}
}
