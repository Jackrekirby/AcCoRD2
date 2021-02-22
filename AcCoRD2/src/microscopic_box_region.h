#pragma once
#include "pch.h"
#include "microscopic_region.h"
#include "microscopic_box_surface_shape.h"

namespace accord::microscopic
{
	class BoxRegion : public Region
	{
	public:
		BoxRegion(shape::basic::Box box, const std::vector<double>& diffision_coefficients, const Vec3i& n_subvolumes,
			double time_step, int priority, const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id);

		const BoxSurfaceShape& GetShape() const;
	private:
		BoxSurfaceShape surface_shape;
	};
}