// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "propensity_object.h"
#include "mesoscopic_layer.h"

namespace accord::mesoscopic
{
	class SecondOrderReaction : public PropensityObject
	{
	public:
		SecondOrderReaction(Layer* reactant_a, Layer* reactant_b, const std::vector<int>& products,
			double reaction_rate, double volume, Subvolume* subvolume);

		void React();

		double UpdatePropensity();

		double GetPropensity();
	private:
		double reaction_propensity;
		double reaction_factor;
		int is_one_reactant;
		Layer* reactant_a;
		Layer* reactant_b;
		std::vector<int> products;
		Subvolume* subvolume;
	};
}
