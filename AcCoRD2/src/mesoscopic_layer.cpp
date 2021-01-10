#include "pch.h"
#include "mesoscopic_layer.h"
#include "vec3d.h"
#include "mesoscopic_layer_neighbour_relationship.h"
#include "propensity_object.h"

namespace accord::mesoscopic
{
	Layer::Layer(double diffusion_coefficient, LinkedPropensityObjects* linked_propensities, MoleculeID id)
		: diffusion_coefficient(diffusion_coefficient), linked_propensities(linked_propensities),
		molecule_count(0), diffusion_propensity(0), id(id)
	{

	}

	void Layer::AddMolecule()
	{
		LOG_INFO("id = {}", id);
		molecule_count++;
		linked_propensities->RequiresUpdate();
	}

	void Layer::RemoveMolecule()
	{
		molecule_count--;
		linked_propensities->RequiresUpdate();
		if (molecule_count < 0)
		{
			LOG_ERROR("attempting to remove molecule when there are no molecules");
			molecule_count = 0;
		}
	}

	int Layer::GetCount()
	{
		return molecule_count;
	}

	void Layer::Diffuse(double index)
	{
		//LOG_INFO("index = {}, count = {}, id = {}", index, molecule_count, id);
		for (auto& relationbship : neighbour_relationships)
		{
			index -= relationbship.GetPropensity();
			if (index < 0)
			{
				RemoveMolecule();
				Layer& neighbour = relationbship.GetNeighbour();
				neighbour.AddMolecule();
				neighbour.linked_propensities->UpdatePropensities();
				return;
			}
		}
		// an event should have occurred by now (unless a floating point error means propensity > 0)
		//LOG_CRITICAL("Layer was selected for a diffusion reaction to occur but none did");
		throw std::exception();
	}


	double Layer::UpdatePropensity()
	{
		//LOG_INFO("updating propensity");
		double new_diffusion_propensity = 0;
		for (auto& neighbour_relationship : neighbour_relationships)
		{
			new_diffusion_propensity += neighbour_relationship.UpdatePropensity(molecule_count);
		}
		double delta_propensity = new_diffusion_propensity - diffusion_propensity;
		diffusion_propensity = new_diffusion_propensity;
		//LOG_INFO("delta propensity = {}", delta_propensity);
		return delta_propensity;
	}

	double Layer::GetPropensity()
	{
		return diffusion_propensity;
	}

	void Layer::AddNeighbourRelationship(Layer* neighbour, double diffusion_factor)
	{
		neighbour_relationships.emplace_back(neighbour, diffusion_factor * diffusion_coefficient);
	}

	double Layer::GetCoefficient()
	{
		return diffusion_coefficient * molecule_count;
	}
}