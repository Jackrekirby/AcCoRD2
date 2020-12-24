#include "pch.h"
#include "microscopic_sphere_region.h"

namespace accord::microscopic
{
	SphereRegion::SphereRegion(shape::basic::Sphere sphere, std::vector<double> diffision_coefficients,
		std::vector<Vec3i> n_subvolumes_per_grid,
		double start_time, double time_step, int priority, EventQueue* event_queue,
		SurfaceType surface_type, RegionID id)
		: Region(diffision_coefficients, n_subvolumes_per_grid, start_time, time_step, 
			priority, event_queue, surface_type, id), surface_shape(sphere)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid);
		LinkGrids();
	}

	const SphereSurfaceShape& SphereRegion::GetShape() const
	{
		return surface_shape;
	}
}