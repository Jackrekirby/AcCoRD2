#pragma once
#include "propensity_object.h"
#include "mesoscopic_layer.h"

namespace accord::mesoscopic
{
	class SecondOrderReaction : public PropensityObject
	{
	public:
		SecondOrderReaction(Layer* reactant_a, Layer* reactant_b, const std::vector<Layer*>& products,
			double reaction_rate, double volume);

		void React();

		double UpdatePropensity();

		double GetPropensity();
	private:
		double reaction_propensity;
		double reaction_factor;
		int is_one_reactant;
		Layer* reactant_a;
		Layer* reactant_b;
		std::vector<Layer*> product_layers;
	};
}
