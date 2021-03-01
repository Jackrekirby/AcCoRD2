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
		LOG_INFO("zeroth order reaction");
		size_t i = 0;
		for (auto& layer : subvolume->GetLayers())
		{
			LOG_INFO("add molecule {}, count {}", products.at(i), layer.GetCount());
			layer.AddMolecule(products.at(i));
			LOG_INFO("addded molecule {}, count {}", products.at(i), layer.GetCount());
			i++;
		}
	}

	double ZerothOrderReaction::GetPropensity()
	{
		return reaction_propensity;
	}
}