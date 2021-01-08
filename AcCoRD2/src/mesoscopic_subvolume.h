#pragma once
#include "pch.h"
#include "object_ids.h"
#include "relation_box.h"

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

	// add json log so u can get a list of all propensities
	class Subvolume
	{
	public:
		Subvolume(const Vec3d& origin, double length, std::vector<double> diffusion_coefficients);

		void CreateLayers(std::vector<double> diffusion_coefficients);

		void AddMolecule(MoleculeID molecule_id);

		void Run();

		void SelectEvent();

		const shape::relation::Box& GetBoundingBox() const;

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

		void UpdatePropensitiesAndTime(double current_time);

		double CalculateTimeToNextReaction();

		// Event Functions

		void LinkToQueue(SubvolumeQueue* queue, size_t queue_index);

		double GetTime() const;

		void UpdateTime(double delta_time);

		bool ReactsBefore(const Subvolume& other);

		void MarkForDeletion();

		bool IsMarkedForDeletion();
	private:
		std::vector<Layer> layers;
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;
		std::vector<SecondOrderReaction> second_order_reactions;
		std::vector<LinkedPropensityObjects> linked_propensity_objects;
		double reaction_propensity;
		shape::relation::Box box;

		// Event Variables
		double time;
		size_t queue_index;
		SubvolumeQueue* queue;

		double CalculateDiffusionFactor(const Subvolume& neighbour);
	};
}