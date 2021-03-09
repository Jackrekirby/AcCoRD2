// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "mesoscopic_layer.h"
#include "vec3d.h"
#include "mesoscopic_layer_neighbour_relationship.h"
#include "propensity_object.h"
#include "mesoscopic_region.h"

namespace accord::mesoscopic
{
	Layer::Layer(double diffusion_coefficient, LinkedPropensityObjects* linked_propensities, MoleculeID id)
		: diffusion_coefficient(diffusion_coefficient), linked_propensities(linked_propensities),
		molecule_count(0), diffusion_propensity(0), id(id)
	{

	}

	void Layer::AddMolecule(int count)
	{
		//LOG_INFO("id = {}", id);
		molecule_count += count;
		linked_propensities->RequiresUpdate();
		//LOG_INFO("molecule count {}", molecule_count);
	}

	void Layer::RemoveMolecule()
	{
		molecule_count--;
		linked_propensities->RequiresUpdate();
		if (molecule_count < 0)
		{
			LOG_CRITICAL("attempting to remove molecule when there are no molecules");
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
		for (auto& relationship : neighbour_relationships)
		{
			index -= relationship.GetPropensity();
			if (index < 0)
			{
				RemoveMolecule();
				Layer& neighbour = relationship.GetNeighbour();
				neighbour.AddMolecule();
				// if the region is not the parent region then propensity should be updated differently?
				neighbour.linked_propensities->UpdatePropensities();
				if (relationship.GetRegion() != nullptr)
				{
					//LOG_INFO("NEIGHBOUR LAYER");
					relationship.GetRegion()->RefreshEventTime();
				}
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

	void Layer::AddNeighbourRelationship(Layer* neighbour, double diffusion_factor, Region* region)
	{
		neighbour_relationships.emplace_back(neighbour, diffusion_factor * diffusion_coefficient, region);
	}

	double Layer::GetCoefficient()
	{
		return diffusion_coefficient * molecule_count;
	}

	void Layer::NextRealisation()
	{
		molecule_count = 0;
		linked_propensities->RequiresUpdate();
	}
}