#pragma once
#include "pch.h"
#include "microscopic_region2.h"
#include "microscopic_sphere_surface_shape.h"

namespace accord::microscopic
{
	class SphereRegion : public Region
	{
	public:
		SphereRegion(shape::basic::Sphere sphere, const std::vector<double>& diffision_coefficients, const std::vector<Vec3i>& n_subvolumes,
			double time_step, int priority, SurfaceType surface_type, const MicroscopicRegionID& id);

		const SphereSurfaceShape& GetShape() const;
	private:
		SphereSurfaceShape surface_shape;
	};
}