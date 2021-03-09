// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "vec3d.h"
#include "molecule_id.h"

namespace accord::microscopic
{
	class Grid;
	class Region;

	// in future will need to make base reaction class with derived VolumeReaction and SurfaceReaction
	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate, double total_reaction_rate, Region* region);

		void Run();
	private:
		Region* region;
		double reaction_probability;
		double min_reaction_time;
		double total_reaction_rate;
		Grid* reaction_grid;
		std::vector<int> products;

		double CalculateMinimumReactionTime(double total_reaction_rate, double region_time_step);

		double CalculateReactionTime();

		void CreateProductMolecules(const Vec3d& position, double reaction_time);

		double CalculateReactionProbability(double reaction_rate, double total_reaction_rate, double region_time_step);

	};
}