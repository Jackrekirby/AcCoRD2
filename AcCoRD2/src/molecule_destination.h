// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3d.h"

namespace accord::microscopic
{
	class Owner;

	class MoleculeDestination
	{
	public:
		MoleculeDestination(Vec3d position, Owner* owner);

		const Vec3d& GetPosition() const;

		Owner& GetOwner() const;
	private:
		Vec3d position;
		Owner* owner;
	};
}
