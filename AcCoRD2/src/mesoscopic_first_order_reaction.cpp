// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "mesoscopic_first_order_reaction.h"
#include "mesoscopic_layer.h"
#include "mesoscopic_subvolume.h"

namespace accord::mesoscopic
{
	FirstOrderReaction::FirstOrderReaction(Layer* reactant, const std::vector<int>& products, double reaction_rate, Subvolume* subvolume)
		: reaction_propensity(0), products(products), reaction_rate(reaction_rate), reactant(reactant), subvolume(subvolume)
	{

	}

	void FirstOrderReaction::React()
	{
		reactant->RemoveMolecule();

		size_t i = 0;
		for (auto& layer : subvolume->GetLayers())
		{
			layer.AddMolecule(products.at(i));
			i++;
		}
	}

	double FirstOrderReaction::UpdatePropensity()
	{
		double old_propensity = reaction_propensity;
		reaction_propensity = reaction_rate * reactant->GetCount();
		return (reaction_propensity - old_propensity);
	}

	double FirstOrderReaction::GetPropensity()
	{
		return reaction_propensity;
	}
}