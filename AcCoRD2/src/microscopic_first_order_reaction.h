#pragma once
#include "pch.h"
#include "object_ids.h"
#include "vec3d.h"

namespace accord::microscopic
{
	class Grid;
	class Region;

	// in future will need to make base reaction class with derived VolumeReaction and SurfaceReaction
	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, double total_reaction_rate, Region* region);

		void Run();
	private:
		Region* region;
		double reaction_probability;
		double min_reaction_time;
		double total_reaction_rate;
		double time;
		Grid* reaction_grid;
		std::vector<Grid*> product_grids;

		double CalculateMinimumReactionTime(double total_reaction_rate, double region_time_step);

		double CalculateReactionTime();

		void CreateProductMolecules(const Vec3d& position, double reaction_time);

		double CalculateReactionProbability(double reaction_rate, double total_reaction_rate, double region_time_step);

		std::vector<Grid*> GetProductGrids(const MoleculeIDs& products);

	};
}