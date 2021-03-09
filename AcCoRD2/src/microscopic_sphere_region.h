// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "microscopic_region.h"
#include "microscopic_sphere_surface_shape.h"

namespace accord::microscopic
{
	class SphereRegion : public Region
	{
	public:
		SphereRegion(shape::basic::Sphere sphere, const std::vector<double>& diffision_coefficients, const Vec3i& n_subvolumes,
			double time_step, int priority, const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id);

		const SphereSurfaceShape& GetShape() const;
	private:
		SphereSurfaceShape surface_shape;
	};
}