// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord::microscopic
{
	class Subvolume;

	class TypedSubvolume
	{
	public:
		void Add(Subvolume& subvolume);

		std::vector<Subvolume*>& GetSubvolumes();

	private:
		std::vector<Subvolume*> subvolumes;
	};
}