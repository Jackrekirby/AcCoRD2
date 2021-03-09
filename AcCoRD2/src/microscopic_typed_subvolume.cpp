// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_typed_subvolume.h"
#include "microscopic_subvolume.h"

namespace accord::microscopic
{
	void TypedSubvolume::Add(Subvolume& subvolume)
	{
		subvolumes.emplace_back(&subvolume);
	}

	std::vector<Subvolume*>& TypedSubvolume::GetSubvolumes()
	{
		return subvolumes;
	}
}