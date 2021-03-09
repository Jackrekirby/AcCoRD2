// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "relation_box.h"
#include "generating_box.h"
#include "mesoscopic_layer.h"
#include "mesoscopic_zeroth_order_reaction.h"
#include "mesoscopic_first_order_reaction.h"
#include "mesoscopic_second_order_reaction.h"
#include "propensity_object.h"
#include "mesoscopic_subvolume_event.h"
#include "vec3i.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::mesoscopic
{
	using SubvolumeID = int;
	using SubvolumeIDs = std::vector<int>;

	class SubvolumeBox : public shape::relation::Box, public shape::generating::Box
	{
	public:
		SubvolumeBox(const Vec3d& origin, double length);

		void ToJson(Json& j) const;
	};

	// add json log so u can get a list of all propensities
	class Subvolume : public SubvolumeEvent
	{
	public:
		Subvolume(const Vec3d& origin, double length, const std::vector<double>& diffusion_coefficients, const Vec3i& relative_position, const SubvolumeID& id);

		void CreateLayers(const std::vector<double>& diffusion_coefficients);

		void AddMolecule(const MoleculeID& molecule_id);

		void Run();

		void SelectEvent();

		const SubvolumeBox& GetBoundingBox() const;

		// assumes the subvolumes are neighbours
		// add IfNeighbourAdd()
		// add a sibling neighbour
		void AddNeighbour(Subvolume& subvolume);

		// add a neighbour owned by a different region
		// region pointer needed so regions event time can be updated
		void AddNeighbour(Subvolume& subvolume, Region* region);

		Layer& GetLayer(const MoleculeID& id);

		std::vector<Layer*> GetLayers(const MoleculeIDs& ids);

		std::vector<Layer>& GetLayers();

		void AddZerothOrderReaction(const std::vector<int>& products, double reaction_rate);

		void AddFirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate);

		void AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b, const std::vector<int>& products, double reaction_rate);

		void AddLinkToPropensityObject(const MoleculeID& id, PropensityObject* object);

		void AddLinkToPropensityObjects(const MoleculeIDs& ids, PropensityObject* object);

		void UpdatePropensities();

		void UpdatePropensities(const MoleculeID& id);

		void UpdatePropensitiesAndTime(double current_time);

		void UpdateReactionTime();

		void UpdateReactionPropensity(double delta_propensity);

		double GetPropensity();

		void MarkForDeletion();

		bool IsMarkedForDeletion();

		void NextRealisation();

		const Vec3i& GetRelativePosition() const;

		SubvolumeID GetID() const;
	private:
		std::vector<Layer> layers;
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;
		std::vector<SecondOrderReaction> second_order_reactions;
		std::vector<LinkedPropensityObjects> linked_propensity_objects;
		Vec3i relative_position;
		double reaction_propensity;
		bool deleteFlag;
		SubvolumeBox box;
		SubvolumeID id;

		double CalculateDiffusionFactor(const Subvolume& neighbour);
	};
}