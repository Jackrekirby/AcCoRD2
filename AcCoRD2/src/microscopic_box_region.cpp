#include "pch.h"
#include "microscopic_box_region.h"

namespace accord::microscopic
{
	BoxRegion::BoxRegion(shape::basic::Box box, const std::vector<double>& diffision_coefficients,
		const std::vector<Vec3i>& n_subvolumes_per_grid, double time_step, int priority,
		SurfaceType surface_type, const MicroscopicRegionID& id)
		: Region(diffision_coefficients, n_subvolumes_per_grid, time_step, priority, surface_type, id), surface_shape(box)
	{
		// could move into FinishRegionConstruction()
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid);
		LinkGrids();
	}

	const BoxSurfaceShape& BoxRegion::GetShape() const
	{
		return surface_shape;
	}
}