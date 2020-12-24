#pragma once
#include "pch.h"
#include "microscopic_region2.h"
#include "microscopic_sphere_surface_shape.h"

namespace accord::microscopic
{
	class SphereRegion : public Region
	{
	public:
		SphereRegion(shape::basic::Sphere sphere, std::vector<double> diffision_coefficients, std::vector<Vec3i> n_subvolumes,
			double start_time, double time_step, int priority, EventQueue* event_queue,
			SurfaceType surface_type, RegionID id);

		const SphereSurfaceShape& GetShape() const;
	private:
		SphereSurfaceShape surface_shape;
	};
}