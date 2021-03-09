// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "microscopic_normal_molecule.h"

namespace accord::microscopic
{
	class RecentMolecule : public NormalMolecule
	{
	public:
		RecentMolecule(Vec3d position, double time);

		double GetTime() const;
	private:
		double time;
	};
}
