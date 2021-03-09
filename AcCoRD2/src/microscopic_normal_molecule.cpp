// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_normal_molecule.h"

namespace accord::microscopic
{
	NormalMolecule::NormalMolecule(Vec3d position)
		: position(position)
	{
		if (isnan(position.x))
		{
			LOG_CRITICAL(position);
			throw std::exception();
		}
		
		
	}

	const Vec3d& NormalMolecule::GetPosition() const
	{
		return position;
	}
}
