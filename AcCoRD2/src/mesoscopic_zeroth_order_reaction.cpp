#include "pch.h"
#include "mesoscopic_zeroth_order_reaction.h"
#include "mesoscopic_subvolume.h"

namespace accord::mesoscopic
{
	ZerothOrderReaction::ZerothOrderReaction(const std::vector<int>& products, double reaction_rate, double volume, Subvolume* subvolume)
		: reaction_propensity(reaction_rate * volume), products(products), subvolume(subvolume)
	{
		//LOG_INFO("propensity = {}", reaction_propensity);
	}

	void ZerothOrderReaction::React()
	{
		size_t i = 0;
		for (auto& layer : subvolume->GetLayers())
		{
			layer.AddMolecule(products.at(i));
			i++;
		}
	}

	double ZerothOrderReaction::GetPropensity()
	{
		return reaction_propensity;
	}
}