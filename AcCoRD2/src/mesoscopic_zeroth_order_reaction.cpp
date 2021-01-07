#include "pch.h"
#include "mesoscopic_zeroth_order_reaction.h"

namespace accord::mesoscopic
{
	ZerothOrderReaction::ZerothOrderReaction(const std::vector<Layer*>& products, double reaction_rate, double volume)
		: reaction_propensity(reaction_rate* volume),
		products(products)
	{

	}

	void ZerothOrderReaction::React()
	{
		for (Layer* product : products)
		{
			product->AddMolecule();
		}
	}

	double ZerothOrderReaction::GetPropensity()
	{
		return reaction_propensity;
	}
}