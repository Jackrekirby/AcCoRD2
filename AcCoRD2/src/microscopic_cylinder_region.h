#pragma once
#include "pch.h"
#include "microscopic_region.h"
#include "microscopic_Cylinder_surface_shape.h"

namespace accord::microscopic
{
	class CylinderRegion : public Region
	{
	public:
		CylinderRegion(shape::basic::Cylinder Cylinder, const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
			double time_step, int priority, SurfaceType surface_type, const MicroscopicRegionID& id);

		const CylinderSurfaceShape& GetShape() const;
	private:
		CylinderSurfaceShape surface_shape;
	};
}