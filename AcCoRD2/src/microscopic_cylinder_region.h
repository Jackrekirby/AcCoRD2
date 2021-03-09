// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "microscopic_region.h"
#include "microscopic_Cylinder_surface_shape.h"

namespace accord::microscopic
{
	class CylinderRegion : public Region
	{
	public:
		CylinderRegion(shape::basic::Cylinder Cylinder, const std::vector<double>& diffision_coefficients, const Vec3i& n_subvolumes,
			double time_step, int priority, const std::vector<SurfaceType>& surface_types, const MicroscopicRegionID& id);

		const CylinderSurfaceShape& GetShape() const;
	private:
		CylinderSurfaceShape surface_shape;
	};
}