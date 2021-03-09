// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_relative.h"
namespace accord::microscopic
{
	class NeighbourRelativeShape;

	class NeighbourRelative : public Relative
	{
	public:
		virtual const NeighbourRelativeShape& GetShape() const = 0;

		virtual bool IsRegion() const = 0;
	};
}