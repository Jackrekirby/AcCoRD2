#include "pch.h"
#include "microscopic_box_region.h"

namespace accord::microscopic
{
	BoxRegion::BoxRegion(shape::basic::Box box, const std::vector<double>& diffision_coefficients,
		const std::vector<Vec3i>& n_subvolumes_per_grid, double time_step, int priority,
		const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id)
		: Region(time_step, priority, id), surface_shape(box)
	{
		// could move into FinishRegionConstruction()
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid, surface_types);
		LinkGrids();
	}

	const BoxSurfaceShape& BoxRegion::GetShape() const
	{
		return surface_shape;
	}
}