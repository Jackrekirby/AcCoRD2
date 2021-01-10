#include "pch.h"
#include "mesoscopic_layer_neighbour_relationship.h"
#include "mesoscopic_layer.h"

namespace accord::mesoscopic
{
	NeighbourRelationship::NeighbourRelationship(Layer* neighbour, double diffusion_factor)
		: neighbour(neighbour), diffusion_factor(diffusion_factor),
		diffusion_propensity(0)
	{

	}

	Layer& NeighbourRelationship::GetNeighbour()
	{
		return *neighbour;
	}

	double NeighbourRelationship::GetDiffusionFactor()
	{
		return diffusion_factor;
	}

	double NeighbourRelationship::GetPropensity()
	{
		return diffusion_propensity;
	}

	double NeighbourRelationship::UpdatePropensity(int molecule_count)
	{
		diffusion_propensity = molecule_count * diffusion_factor;
		//LOG_INFO("Updating Propensity {}", diffusion_propensity);
		return diffusion_propensity;
	}
}