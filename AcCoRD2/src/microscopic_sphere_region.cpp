#include "pch.h"
#include "microscopic_sphere_region.h"

namespace accord::microscopic
{
	SphereRegion::SphereRegion(shape::basic::Sphere sphere, const std::vector<double>& diffision_coefficients,
		const std::vector<Vec3i>& n_subvolumes_per_grid, double time_step, int priority,
		const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id)
		: Region(time_step, priority, id), surface_shape(sphere)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid, surface_types);
		LinkGrids();
	}

	const SphereSurfaceShape& SphereRegion::GetShape() const
	{
		return surface_shape;
	}
}