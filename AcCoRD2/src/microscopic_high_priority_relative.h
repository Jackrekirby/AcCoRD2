// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_relative.h"
namespace accord::microscopic
{
	class HighPriorityRelativeShape;

	class HighPriorityRelative : public Relative
	{
	public:
		enum class SurfaceDirection
		{
			Internal, External, Both
		};

		virtual const SurfaceDirection& GetSurfaceDirection() const = 0;

		virtual const HighPriorityRelativeShape& GetShape() const = 0;
	};

	void from_json(const Json& j, HighPriorityRelative::SurfaceDirection& surface_direction);
}