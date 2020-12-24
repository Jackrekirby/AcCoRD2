#pragma once
#include "pch.h"
#include "object_ids.h"

namespace accord::microscopic
{
	class Grid;
	class Region;

	// in future will need to make base reaction class with derived VolumeReaction and SurfaceReaction
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, Region* region);

		void NextRealisation();

		void Run();
	private:
		Region* region;
		double reaction_coefficient;
		double time;
		std::vector<Grid*> product_grids;

		void CreateProductMolecules();

		double GenerateNextReactionTime();

		double CalculateStartTime();

		double CalculateReactionCoefficient(double reaction_rate);

		std::vector<Grid*> GetProductGrids(const MoleculeIDs& products);

	};
}