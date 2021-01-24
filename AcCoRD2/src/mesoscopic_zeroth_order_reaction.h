#pragma once

namespace accord::mesoscopic
{
	class Subvolume;

	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const std::vector<int>& products, double reaction_rate, double volume, Subvolume* subvolume);

		void React();

		double GetPropensity();
	private:
		double reaction_propensity;
		std::vector<int> products;
		Subvolume* subvolume;
	};
}