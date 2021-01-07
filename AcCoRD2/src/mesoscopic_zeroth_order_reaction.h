#pragma once
#include "mesoscopic_layer.h"

namespace accord::mesoscopic
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const std::vector<Layer*>& products, double reaction_rate, double volume);

		void React();

		double GetPropensity();
	private:
		double reaction_propensity;
		std::vector<Layer*> products;
	};
}