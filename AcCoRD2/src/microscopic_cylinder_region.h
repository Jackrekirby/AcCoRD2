#pragma once
#include "pch.h"
#include "microscopic_region2.h"
#include "microscopic_Cylinder_surface_shape.h"

namespace accord::microscopic
{
	class CylinderRegion : public Region
	{
	public:
		CylinderRegion(shape::basic::Cylinder Cylinder, std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes,
			double start_time, double time_step, int priority, EventQueue* event_queue,
			SurfaceType surface_type, RegionID id);

		const CylinderSurfaceShape& GetShape() const;
	private:
		CylinderSurfaceShape surface_shape;
	};
}