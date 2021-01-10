#pragma once
#include "pch.h"
#include "microscopic_region2.h"
#include "microscopic_box_surface_shape.h"

namespace accord::microscopic
{
	class BoxRegion : public Region
	{
	public:
		BoxRegion(shape::basic::Box box, std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes,
			double start_time, double time_step, int priority,
			SurfaceType surface_type, MicroRegionID id);

		const BoxSurfaceShape& GetShape() const;
	private:
		BoxSurfaceShape surface_shape;
	};
}