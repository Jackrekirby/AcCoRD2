#include "pch.h"
#include "mesoscopic_first_order_reaction.h"
#include "mesoscopic_layer.h"

namespace accord::mesoscopic
{
	FirstOrderReaction::FirstOrderReaction(Layer* reactant, const std::vector<Layer*>& products, double reaction_rate)
		: reaction_propensity(0), products(products), reaction_rate(reaction_rate), reactant(reactant)
	{

	}

	void FirstOrderReaction::React()
	{
		reactant->RemoveMolecule();
		for (Layer* product : products)
		{
			product->AddMolecule();
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