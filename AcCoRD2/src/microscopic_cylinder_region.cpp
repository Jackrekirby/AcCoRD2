// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_cylinder_region.h"

namespace accord::microscopic
{
	CylinderRegion::CylinderRegion(shape::basic::Cylinder Cylinder, const std::vector<double>& diffision_coefficients,
		const Vec3i& n_subvolumes, double time_step, int priority,
		const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id)
		: Region(time_step, priority, id), surface_shape(Cylinder)
	{
		GenerateGrids(diffision_coefficients, n_subvolumes, surface_types);
		LinkGrids();
	}

	const CylinderSurfaceShape& CylinderRegion::GetShape() const
	{
		return surface_shape;
	}
}