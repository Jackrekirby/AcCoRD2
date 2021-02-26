#pragma once
#include "microscopic_surface.h"
#include "microscopic_box_surface_shape.h"
#include "vec3d.h"

namespace accord::microscopic
{
	// join box surface and box surface shape into a single class
	class BoxSurface : public Surface
	{
	public:
		BoxSurface(Vec3d origin, Vec3d length, Type type);

		BoxSurfaceShape& GetShape();

	private:
		BoxSurfaceShape box;
		Type type;
	};
}