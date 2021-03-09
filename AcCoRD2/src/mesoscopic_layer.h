// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "mesoscopic_layer_neighbour_relationship.h"
#include "propensity_object.h"
#include "molecule_id.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::mesoscopic
{
	class LinkedPropensityObjects;
	class Subvolume;
	class Region;

	class Layer : public PropensityObject
	{
	public:
		Layer(double diffusion_coefficient, LinkedPropensityObjects* linked_propensities, MoleculeID id);

		void AddMolecule(int count = 1);

		void RemoveMolecule();

		int GetCount();

		void Diffuse(double index);

		double UpdatePropensity();

		double GetPropensity();

		void AddNeighbourRelationship(Layer* neighbour, double diffusion_factor, Region* region = nullptr);

		double GetCoefficient();

		void NextRealisation();
	private:
		std::vector<NeighbourRelationship> neighbour_relationships;
		int molecule_count;
		double diffusion_propensity; // the total propensity of all diffision reactions
		double diffusion_coefficient; // the diffision coefficient of the molecule type
		LinkedPropensityObjects* linked_propensities;
		MoleculeID id;
	};
}