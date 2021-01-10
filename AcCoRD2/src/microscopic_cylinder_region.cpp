#include "pch.h"
#include "microscopic_cylinder_region.h"

namespace accord::microscopic
{
	CylinderRegion::CylinderRegion(shape::basic::Cylinder Cylinder, std::vector<double> diffision_coefficients,
		std::vector<Vec3i> n_subvolumes_per_grid,
		double start_time, double time_step, int priority,
		SurfaceType surface_type, MicroRegionID id)
		: Region(diffision_coefficients, n_subvolumes_per_grid, start_time, time_step, 
			priority, surface_type, id), surface_shape(Cylinder)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes_per_grid);
		LinkGrids();
	}

	const CylinderSurfaceShape& CylinderRegion::GetShape() const
	{
		return surface_shape;
	}
}