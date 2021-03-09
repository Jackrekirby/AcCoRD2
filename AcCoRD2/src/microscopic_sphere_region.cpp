// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_sphere_region.h"

namespace accord::microscopic
{
	SphereRegion::SphereRegion(shape::basic::Sphere sphere, const std::vector<double>& diffision_coefficients,
		const Vec3i& n_subvolumes, double time_step, int priority,
		const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id)
		: Region(time_step, priority, id), surface_shape(sphere)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes, surface_types);
		LinkGrids();
	}

	const SphereSurfaceShape& SphereRegion::GetShape() const
	{
		return surface_shape;
	}
}