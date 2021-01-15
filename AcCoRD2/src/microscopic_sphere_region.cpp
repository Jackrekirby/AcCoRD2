#include "pch.h"
#include "microscopic_sphere_region.h"

namespace accord::microscopic
{
	SphereRegion::SphereRegion(shape::basic::Sphere sphere, const std::vector<double>& diffision_coefficients,
		const std::vector<Vec3i>& n_subvolumes_per_grid, double time_step, int priority,
		SurfaceType surface_type, const MicroscopicRegionID& id)
		: Region(diffision_coefficients, n_subvolumes_per_grid, time_step, priority, surface_type, id), surface_shape(sphere)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid);
		LinkGrids();
	}

	const SphereSurfaceShape& SphereRegion::GetShape() const
	{
		return surface_shape;
	}
}