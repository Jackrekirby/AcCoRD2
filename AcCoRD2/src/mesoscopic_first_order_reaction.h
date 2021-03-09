// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "propensity_object.h"

namespace accord::mesoscopic
{
	class Layer;
	class Subvolume;

	class FirstOrderReaction : public PropensityObject
	{
	public:
		FirstOrderReaction(Layer* reactant, const std::vector<int>& products, double reaction_rate, Subvolume* subvolume);

		void React();

		double UpdatePropensity();

		double GetPropensity();

	private:
		double reaction_propensity;
		double reaction_rate;
		Layer* reactant;
		std::vector<int> products;
		Subvolume* subvolume;
	};
}