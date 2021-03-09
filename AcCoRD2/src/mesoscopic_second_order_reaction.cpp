// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "mesoscopic_second_order_reaction.h"
#include "mesoscopic_subvolume.h"

namespace accord::mesoscopic
{
	SecondOrderReaction::SecondOrderReaction(Layer* reactant_a, Layer* reactant_b, const std::vector<int>& products,
		double reaction_rate, double volume, Subvolume* subvolume)
		: reaction_factor(reaction_rate / volume), reactant_a(reactant_a), reactant_b(reactant_b),
		is_one_reactant(reactant_a == reactant_b), products(products), reaction_propensity(0), subvolume(subvolume)
	{
		//LOG_INFO("volume = {}, reaction rate = {}, reaction_factor = {}", volume, reaction_rate, reaction_factor);
	}

	void SecondOrderReaction::React()
	{
		reactant_a->RemoveMolecule();
		reactant_b->RemoveMolecule();
		size_t i = 0;
		for (auto& layer : subvolume->GetLayers())
		{
			layer.AddMolecule(products.at(i));
			i++;
		}
	}

	double SecondOrderReaction::UpdatePropensity()
	{
		double old_propensity = reaction_propensity;
		reaction_propensity = static_cast<double>(reactant_a->GetCount() * (reactant_b->GetCount() - is_one_reactant)) * reaction_factor;
		//LOG_INFO("a {} b {}, reaction_propensity = {}", reactant_a->GetCount(), reactant_b->GetCount(), reaction_propensity);
		return reaction_propensity - old_propensity;
	}

	double SecondOrderReaction::GetPropensity()
	{
		return reaction_propensity;
	}
}
