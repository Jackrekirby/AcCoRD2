#include "pch.h"
#include "mesoscopic_subvolume.h"
#include "vec3d.h"
#include "subvolume_queue.h"
#include "mesoscopic_layer.h"
#include "environment.h"

namespace accord::mesoscopic
{
	SubvolumeBox::SubvolumeBox(const Vec3d& origin, double length)
		: shape::relation::Box(origin, Vec3d(length)), shape::generating::Box(origin, Vec3d(length)),
		shape::basic::Box(origin, Vec3d(length))
	{

	}

	void SubvolumeBox::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Box>(*this);
	}

	Subvolume::Subvolume(const Vec3d& origin, double length, std::vector<double> diffusion_coefficients, double start_time, SubvolumeID id)
		: box(origin, length), reaction_propensity(0), queue(nullptr), queue_index(0), time(start_time), id(id)
	{
		CreateLayers(diffusion_coefficients);
	}

	void Subvolume::CreateLayers(std::vector<double> diffusion_coefficients)
	{
		linked_propensity_objects.reserve(diffusion_coefficients.size());
		layers.reserve(diffusion_coefficients.size());
		MoleculeID i = 0;
		for (auto& diffusion_coefficient : diffusion_coefficients)
		{
			linked_propensity_objects.emplace_back(this);
			linked_propensity_objects.back().RequiresUpdate();
			layers.emplace_back(diffusion_coefficient, &linked_propensity_objects.at(i), i);
			AddLinkToPropensityObject(i, &layers.back());
			i++;
		}
	}

	void Subvolume::AddMolecule(MoleculeID molecule_id)
	{
		layers.at(molecule_id).AddMolecule();
		UpdatePropensities(molecule_id); // switch to ratio method
		// e.g. CalculateTime and ModifyTime or simply use function args
		//UpdateReactionTime();
	}

	void Subvolume::Run()
	{
		//LOG_INFO("subvolume id = {}", id);
		// change event to reaction
		SelectEvent();
		UpdatePropensities();
		// update next event time
	}

	void Subvolume::SelectEvent()
	{
		double index = Random::GenerateRealUniform(0, reaction_propensity);
		//LOG_INFO("starting index = {}", index);
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
		//LOG_INFO("pre-diffusion index = {}", index);
		for (auto& layer : layers)
		{
			index -= layer.GetPropensity();
			if (index < 0) { layer.Diffuse(-index); return; }
		}
		// an event should have occurred by now (unless a floating point error means propensity > 0)
		LOG_CRITICAL("Subvolume was selected for a reaction to occur but none did");
		throw std::exception();
	}

	const SubvolumeBox& Subvolume::GetBoundingBox() const
	{
		return box;
	}

	// assumes the subvolums are neighbours
	// add IfNeighbourAdd()
	void Subvolume::AddNeighbour(Subvolume& subvolume)
	{
		//LOG_INFO("add neighbour");
		double diffusion_factor = CalculateDiffusionFactor(subvolume);
		MoleculeID i = 0;
		for (auto& layer : layers)
		{
			layer.AddNeighbourRelationship(&subvolume.GetLayer(i), diffusion_factor);
			i++;
		}
	}

	void Subvolume::AddNeighbour(Subvolume& subvolume, Region* region)
	{
		double diffusion_factor = CalculateDiffusionFactor(subvolume);
		MoleculeID i = 0;
		for (auto& layer : layers)
		{
			layer.AddNeighbourRelationship(&subvolume.GetLayer(i), diffusion_factor, region);
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
		reaction_propensity += zeroth_order_reactions.back().GetPropensity();
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
		linked_propensity_objects.at(id).Add(object);
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
			linked_propensity_object.UpdatePropensities();
		}
	}

	void Subvolume::UpdatePropensities(MoleculeID id)
	{
		// only updates the propensity of objects which are affected by a change in molecule count
		linked_propensity_objects.at(id).UpdatePropensities();
	}

	// likely not needed, you should know which molecule types need updating
	void Subvolume::UpdatePropensitiesAndTime(double current_time)
	{
		// only updates the propensity of objects which are affected by a change in molecule count
		double old_propensity = reaction_propensity;
		for (auto& linked_propensity_object : linked_propensity_objects)
		{
			linked_propensity_object.UpdatePropensities();
		}
		//UpdateReactionTime();
		//SetTime(current_time + (old_propensity / reaction_propensity) * (time - current_time));
	}

	void Subvolume::UpdateReactionTime()
	{
		// Changed environment.GetTime() to region.GetTime() so subvolume reactions times can be offset from the regions start time
		// it is incorrect to keep updating form environment time as if another object updates the subvolume then event the same propensity
		// will result in a later subvolume reaction time.

		// this (using parent) is the incorrect way to update the reaction time if it is not a subvolume event as event time has since updated 
		// CORRECTED by updating and not setting time

		SetTime(Environment::GetTime() - log(Random::GenerateRealUniform()) / reaction_propensity);
		UpdateTime(-log(Random::GenerateRealUniform()) / reaction_propensity);
		//LOG_INFO("time = {}", GetTime());
	}

	void Subvolume::UpdateReactionPropensity(double delta_propensity)
	{
		//LOG_INFO("new reaction propensity = {}, {}", reaction_propensity, delta_propensity);
		reaction_propensity += delta_propensity;
	}

	double Subvolume::GetPropensity()
	{
		return reaction_propensity;
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

	void Subvolume::SetTime(double new_time)
	{
		if (new_time > time)
		{
			//LOG_INFO("increasing time");
			time = new_time;
			queue->DecreasePriority(queue_index);
		}
		else
		{
			//LOG_INFO("decreasing time");
			time = new_time;
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

	void Subvolume::MarkForDeletion()
	{
		time = -1;
	}

	bool Subvolume::IsMarkedForDeletion()
	{
		return (time == -1);
	}

	// could store start time locally instead
	void Subvolume::NextRealisation(double start_time)
	{
		SetTime(start_time);
		for (auto& layer : layers)
		{
			layer.NextRealisation();
		}
		UpdatePropensities();
	}

	SubvolumeID Subvolume::GetID() const
	{
		return id;
	}

	double Subvolume::CalculateDiffusionFactor(const Subvolume& neighbour)
	{
		auto area = GetBoundingBox().CalculateAreaBetweenNeighbouringBoxes(neighbour.GetBoundingBox());
		auto& length1 = GetBoundingBox().GetLength().x;
		auto& length2 = neighbour.GetBoundingBox().GetLength().x;
		return (2 * area) / (std::pow(length1, 3) * (length1 + length2));
	}
}