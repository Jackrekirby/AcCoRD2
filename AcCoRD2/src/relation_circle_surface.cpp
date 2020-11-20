#include "pch.h"
#include "relation_circle_surface_3d.h"

namespace accord::shape::relation
{
	BoxSurface3D::BoxSurface3D(Plane3D plane, Circle circle)
		: Surface3D(plane), circle(circle)
	{

	}

	const Circle& BoxSurface3D::GetShape() const
	{
		return circle;
	}
}
