#include "pch.h"
#include "mesoscopic_second_order_reaction.h"

namespace accord::mesoscopic
{
	SecondOrderReaction::SecondOrderReaction(Layer* reactant_a, Layer* reactant_b, const std::vector<Layer*>& products,
		double reaction_rate, double volume)
		: reaction_factor(reaction_rate / volume), reactant_a(reactant_a), reactant_b(reactant_b),
		is_one_reactant(reactant_a == reactant_b), product_layers(products), reaction_propensity(0)
	{

	}

	void SecondOrderReaction::React()
	{
		reactant_a->RemoveMolecule();
		reactant_b->RemoveMolecule();
		for (Layer* layer : product_layers)
		{
			layer->AddMolecule();
		}
	}

	double SecondOrderReaction::UpdatePropensity()
	{
		double old_propensity = reaction_propensity;
		reaction_propensity = static_cast<double>(reactant_a->GetCount() * (reactant_b->GetCount() - is_one_reactant)) * reaction_factor;
		return reaction_propensity - old_propensity;
	}

	double SecondOrderReaction::GetPropensity()
	{
		return reaction_propensity;
	}
}
