#pragma once
#include "propensity_object.h"

namespace accord::mesoscopic
{
	class Layer;

	class FirstOrderReaction : public PropensityObject
	{
	public:
		FirstOrderReaction(Layer* reactant, const std::vector<Layer*>& products, double reaction_rate);

		void React();

		double UpdatePropensity();

		double GetPropensity();

	private:
		double reaction_propensity;
		double reaction_rate;
		Layer* reactant;
		std::vector<Layer*> products;
	};
}