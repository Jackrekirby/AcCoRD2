// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once

namespace accord::mesoscopic
{
	class Subvolume;

	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const std::vector<int>& products, double reaction_rate, double volume, Subvolume* subvolume);

		void React();

		double GetPropensity();
	private:
		double reaction_propensity;
		std::vector<int> products;
		Subvolume* subvolume;
	};
}