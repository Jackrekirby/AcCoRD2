#pragma once

namespace accord::mesoscopic
{
	class Layer;
	class Region;

	class NeighbourRelationship
	{
	public:
		NeighbourRelationship(Layer* neighbour, double diffusion_factor, Region* region);

		Layer& GetNeighbour();

		Region* GetRegion();

		double GetDiffusionFactor();

		double GetPropensity();

		double UpdatePropensity(int molecule_count);
	private:
		double diffusion_propensity;
		double diffusion_factor;
		Layer* neighbour;
		Region* region;
	};
}