#pragma once
#include "pch.h"
#include "molecule_id.h"

namespace accord::microscopic
{
	class Grid;
	class Region;

	// in future will need to make base reaction class with derived VolumeReaction and SurfaceReaction
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const std::vector<int>& products, double reaction_rate, Region* region);

		void NextRealisation();

		void Run();
	private:
		Region* region;
		double reaction_coefficient;
		double time;
		std::vector<int> products;

		void CreateProductMolecules();

		double GenerateNextReactionTime();

		double CalculateReactionCoefficient(double reaction_rate);
	};
}