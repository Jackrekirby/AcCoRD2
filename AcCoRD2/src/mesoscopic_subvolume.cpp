#include "pch.h"
#include "mesoscopic_subvolume.h"
#include "vec3d.h"
#include "subvolume_queue.h"
#include "mesoscopic_layer.h"

namespace accord::mesoscopic
{

	Subvolume::Subvolume(const Vec3d& origin, double length, std::vector<double> diffusion_coefficients)
		: box(origin, Vec3d(length))
	{

	}

	void Subvolume::AddMolecule(MoleculeID molecule_id)
	{
		layers.at(molecule_id).AddMolecule();
	}

	void Subvolume::Run()
	{
		// change event to reaction
		SelectEvent();
		UpdatePropensities();
		// update next event time
		UpdateTime(CalculateTimeToNextReaction());
	}

	void Subvolume::SelectEvent()
	{
		double index = Random::GenerateRealUniform(0, reaction_propensity);
		for (auto& reaction : zeroth_order_reactions)
		{
			index -= reaction.GetPropensity();
			if (index < 0) { reaction.React(); return; }
		}

		for (auto& reaction : first_order_reactions)
		{
			index -= reaction.GetPropensity();
			if (index < 0) { reaction.React(); return; }
		}

		for (auto& reaction : second_order_reactions)
		{
			index -= reaction.GetPropensity();
			if (index < 0) { reaction.React(); return; }
		}

		for (auto& layer : layers)
		{
			index -= layer.GetPropensity();
			if (index < 0) { layer.Diffuse(-index); return; }
		}
		// an event should have occurred by now (unless a floating point error means propensity > 0)
		LOG_CRITICAL("Subvolume was selected for a reaction to occur but none did");
		throw std::exception();
	}

	const shape::relation::Box& Subvolume::GetBoundingBox() const
	{
		return box;
	}

	// assumes the subvolums are neighbours
	// add IfNeighbourAdd()
	void Subvolume::AddNeighbour(Subvolume& subvolume)
	{
		double diffusion_factor = CalculateDiffusionFactor(subvolume);
		MoleculeID i = 0;
		for (auto& layer : layers)
		{
			layer.AddNeighbourRelationship(&subvolume.GetLayer(i), diffusion_factor);
			i++;
		}
	}

	Layer& Subvolume::GetLayer(MoleculeID id)
	{
		return layers.at(id);
	}

	std::vector<Layer*> Subvolume::GetLayers(MoleculeIDs ids)
	{
		std::vector<Layer*> layer_ptrs;
		layer_ptrs.reserve(ids.size());
		for (auto& id : ids)
		{
			layer_ptrs.emplace_back(&GetLayer(id));
		}
		return layer_ptrs;
	}

	void Subvolume::AddZerothOrderReaction(MoleculeIDs products, double reaction_rate)
	{
		zeroth_order_reactions.emplace_back(GetLayers(products), reaction_rate, GetBoundingBox().CalculateVolume());
	}

	void Subvolume::AddFirstOrderReaction(MoleculeID reactant, MoleculeIDs products, double reaction_rate)
	{
		first_order_reactions.emplace_back(&GetLayer(reactant), GetLayers(products), reaction_rate);
		AddLinkToPropensityObject(reactant, &first_order_reactions.back());
		AddLinkToPropensityObjects(products, &first_order_reactions.back());
	}

	void Subvolume::AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, MoleculeIDs products, double reaction_rate)
	{
		second_order_reactions.emplace_back(&GetLayer(reactant_a), &GetLayer(reactant_b), GetLayers(products),
			reaction_rate, GetBoundingBox().CalculateVolume());
		AddLinkToPropensityObjects({ reactant_a, reactant_b }, &second_order_reactions.back());
		AddLinkToPropensityObjects(products, &second_order_reactions.back());
	}

	void Subvolume::AddLinkToPropensityObject(MoleculeID id, PropensityObject* object)
	{
		linked_propensity_objects.at(id)->Add(object);
	}

	void Subvolume::AddLinkToPropensityObjects(MoleculeIDs ids, PropensityObject* object)
	{
		for (MoleculeID id : ids)
		{
			AddLinkToPropensityObject(id, object);
		}
	}

	void Subvolume::UpdatePropensities()
	{
		// only updates the propensity of objects which are affected by a change in molecule count
		for (auto& linked_propensity_object : linked_propensity_objects)
		{
			reaction_propensity += linked_propensity_object->UpdatePropensities();
		}
	}

	double Subvolume::CalculateTimeToNextReaction()
	{
		return -log(Random::GenerateRealUniform()) / reaction_propensity;
	}

	void Subvolume::LinkToQueue(SubvolumeQueue* queue, size_t queue_index)
	{
		this->queue = queue;
		this->queue_index = queue_index;
	}

	double Subvolume::GetTime() const
	{
		return time;
	}

	void Subvolume::UpdateTime(double delta_time)
	{
		// negative delta time should never occur. Consider removing.
		if (delta_time > 0)
		{
			time += delta_time;
			queue->DecreasePriority(queue_index);
		}
		else
		{
			time += delta_time;
			queue->IncreasePriority(queue_index);
		}
	}

	bool Subvolume::ReactsBefore(const Subvolume& other)
	{
		if (time == other.time)
		{
			return (Random::GenerateRealUniform() > 0.5);
		}
		return (time < other.time);
	}

	double Subvolume::CalculateDiffusionFactor(const Subvolume& neighbour)
	{
		auto area = GetBoundingBox().CalculateAreaBetweenNeighbouringBoxes(neighbour.GetBoundingBox());
		auto& length1 = GetBoundingBox().GetLength().x;
		auto& length2 = neighbour.GetBoundingBox().GetLength().x;
		return (2 * area) / (std::pow(length1, 3) * (length1 + length2));
	}
}