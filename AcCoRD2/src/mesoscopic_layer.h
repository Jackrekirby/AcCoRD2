#pragma once
#include "pch.h"
#include "object_ids.h"
#include "mesoscopic_layer_neighbour_relationship.h"
#include "propensity_object.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::mesoscopic
{
	class LinkedPropensityObjects;
	class Subvolume;

	class Layer : public PropensityObject
	{
	public:

		Layer(double diffusion_coefficient, LinkedPropensityObjects* linked_propensities, MoleculeID id);

		void AddMolecule();

		void RemoveMolecule();

		int GetCount();

		void Diffuse(double index);

		double UpdatePropensity();

		double GetPropensity();

		void AddNeighbourRelationship(Layer* neighbour, double diffusion_factor);

		double GetCoefficient();
	private:
		std::vector<NeighbourRelationship> neighbour_relationships;
		int molecule_count;
		double diffusion_propensity; // the total propensity of all diffision reactions
		double diffusion_coefficient; // the diffision coefficient of the molecule type
		LinkedPropensityObjects* linked_propensities;
		MoleculeID id;
	};
}