// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3d.h"
// can be a mesoregion, grid or adsorbing surface
// time not needed by meso but can just ignore it
namespace accord::microscopic
{
	class Owner
	{
	public:
		virtual void AddMolecule(const Vec3d& position, double time) = 0;

		// probably not required
		virtual void AddMolecule(const Vec3d& position) = 0;
	};
}