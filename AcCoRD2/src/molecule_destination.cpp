// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "molecule_destination.h"
#include "microscopic_owner.h"

namespace accord::microscopic
{
	MoleculeDestination::MoleculeDestination(Vec3d position, Owner* owner)
		: position(position), owner(owner)
	{
		if (isnan(position.x))
		{
			LOG_CRITICAL(position);
			throw std::exception();
		}
	}

	const Vec3d& MoleculeDestination::GetPosition() const
	{
		return position;
	}

	Owner& MoleculeDestination::GetOwner() const
	{
		return *owner;
	}
}