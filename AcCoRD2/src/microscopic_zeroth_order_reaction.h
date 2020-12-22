#pragma once
#include "pch.h"
#include "object_ids.h"

namespace accord::microscopic
{
	class Grid2;
	class Region2;

	// in future will need to make base reaction class with derived VolumeReaction and SurfaceReaction
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, Region2* region);

		void NextRealisation();

		void Run();
	private:
		Region2* region;
		double reaction_coefficient;
		double time;
		std::vector<Grid2*> product_grids;

		void CreateProductMolecules();

		double GenerateNextReactionTime();

		double CalculateStartTime();

		double CalculateReactionCoefficient(double reaction_rate);

		std::vector<Grid2*> GetProductGrids(const MoleculeIDs& products);

	};
}