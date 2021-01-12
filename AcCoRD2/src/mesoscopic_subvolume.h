#pragma once
#include "pch.h"
#include "object_ids.h"
#include "relation_box.h"
#include "generating_box.h"

#include "mesoscopic_layer.h"
#include "mesoscopic_zeroth_order_reaction.h"
#include "mesoscopic_first_order_reaction.h"
#include "mesoscopic_second_order_reaction.h"
#include "propensity_object.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::mesoscopic
{
	class SubvolumeQueue;

	class SubvolumeBox : public shape::relation::Box, public shape::generating::Box
	{
	public:
		SubvolumeBox(const Vec3d& origin, double length);

		void ToJson(Json& j) const;
	};

	// add json log so u can get a list of all propensities
	class Subvolume
	{
	public:
		Subvolume(const Vec3d& origin, double length, std::vector<double> diffusion_coefficients, SubvolumeID id);

		void CreateLayers(std::vector<double> diffusion_coefficients);

		void AddMolecule(MoleculeID molecule_id);

		void Run();

		void SelectEvent();

		const SubvolumeBox& GetBoundingBox() const;

		// assumes the subvolums are neighbours
		// add IfNeighbourAdd()
		void AddNeighbour(Subvolume& subvolume);

		Layer& GetLayer(MoleculeID id);

		std::vector<Layer*> GetLayers(MoleculeIDs ids);

		void AddZerothOrderReaction(MoleculeIDs products, double reaction_rate);

		void AddFirstOrderReaction(MoleculeID reactant, MoleculeIDs products, double reaction_rate);

		void AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, MoleculeIDs products, double reaction_rate);

		void AddLinkToPropensityObject(MoleculeID id, PropensityObject* object);

		void AddLinkToPropensityObjects(MoleculeIDs ids, PropensityObject* object);

		void UpdatePropensities();

		void UpdatePropensities(MoleculeID id);

		void UpdatePropensitiesAndTime(double current_time);

		void UpdateReactionTime();

		void UpdateReactionPropensity(double delta_propensity);

		double GetPropensity();

		// Event Functions

		void LinkToQueue(SubvolumeQueue* queue, size_t queue_index);

		double GetTime() const;

		void UpdateTime(double delta_time);

		void SetTime(double new_time);

		bool ReactsBefore(const Subvolume& other);

		void MarkForDeletion();

		bool IsMarkedForDeletion();

		SubvolumeID GetID() const;
	private:
		std::vector<Layer> layers;
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;
		std::vector<SecondOrderReaction> second_order_reactions;
		std::vector<LinkedPropensityObjects> linked_propensity_objects;
		double reaction_propensity;
		SubvolumeBox box;

		// Event Variables
		double time;
		size_t queue_index;
		SubvolumeQueue* queue;
		SubvolumeID id;

		double CalculateDiffusionFactor(const Subvolume& neighbour);
	};
}