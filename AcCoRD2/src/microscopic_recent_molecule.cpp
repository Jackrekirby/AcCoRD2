// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_recent_molecule.h"

namespace accord::microscopic
{
	RecentMolecule::RecentMolecule(Vec3d position, double time)
		: NormalMolecule(position), time(time)
	{

	}

	double RecentMolecule::GetTime() const
	{
		return time;
	}
}
