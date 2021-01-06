#pragma once
#include "pch.h"
#include "vec3d.h"
#include "vec3i.h"
#include "relation_box.h"
#include "object_ids.h"
#include "event_queue2.h"
#include "event2.h"

namespace accord::mesoscopic
{
	class LinkedPropensityObjects;

	class Neighbour;
	class Layer : public PropensityObject
	{
	public:

		Layer(const Vec3d& origin, double length, double diffusion_coefficient, LinkedPropensityObjects* linked_propensities)
			: diffusion_propensity_coefficient(CalculateDiffusionPropensityCoefficient(length, diffusion_coefficient))
		{

		}

		void AddMolecule()
		{
			molecule_count++;
			linked_propensities->RequiresUpdate();
		}

		void RemoveMolecule()
		{
			molecule_count--;
			linked_propensities->RequiresUpdate();
			if (molecule_count < 0)
			{
				LOG_ERROR("attempting to remove molecule when there are no molecules");
				molecule_count = 0;
			}
		}

		int GetCount()
		{
			return molecule_count;
		}

		void Diffuse(double index)
		{
			for (auto& neighbour : neighbours)
			{
				index -= neighbour.GetPropensity();
				if (index < 0)
				{
					RemoveMolecule();
					neighbour.GetNeighbour().AddMolecule();
				}
			}
			// an event should have occurred by now (unless a floating point error means propensity > 0)
			LOG_CRITICAL("Layer was selected for a diffusion reaciton to occur but none did");
			throw std::exception();
		}


		double UpdatePropensity()
		{
			double new_diffusion_propensity = 0;
			for (auto& neighbour_relationship : neighbour_relationships)
			{
				new_diffusion_propensity += neighbour_relationship.UpdatePropensity(molecule_count);
			}
			double delta_propensity = new_diffusion_propensity - diffusion_propensity;
			diffusion_propensity = new_diffusion_propensity;
			return delta_propensity;
		}

		double GetPropensity()
		{
			return diffusion_propensity;
		}

		void AddNeighbourRelationship(Layer* neighbour, double diffusion_factor)
		{
			neighbour_relationships.emplace_back(neighbour, diffusion_factor * diffusion_coefficient);
		}

		double GetCoefficient()
		{
			return diffusion_coefficient * molecule_count;
		}

		MoleculeID GetMoleculeID()
		{
			return molecule_id;
		}
	private:
		std::vector<NeighbourRelationship> neighbour_relationships;
		int molecule_count;
		double diffusion_propensity;
		double diffusion_coefficient;
		MoleculeID molecule_id;
		LinkedPropensityObjects* linked_propensities;
	};

	class NeighbourRelationship
	{
	public:
		NeighbourRelationship(Layer& neighbour, double diffusion_factor)
			: neighbour(&neighbour), diffusion_factor(diffusion_factor),
			diffusion_propensity(0)
		{

		}

		Layer& GetNeighbour()
		{
			return *neighbour;
		}

		double GetDiffusionFactor()
		{
			return diffusion_factor;
		}

		double GetPropensity()
		{
			return diffusion_propensity;
		}

		double UpdatePropensity(int molecule_count)
		{
			diffusion_propensity = molecule_count * diffusion_factor;
			return diffusion_propensity;
		}
	private:
		double diffusion_propensity;
		double diffusion_factor;
		Layer* neighbour;

	};

	class ZerothOrderReaction : public PropensityObject
	{
	public:
		ZerothOrderReaction(std::vector<Layer*> products, double reaction_rate, double volume)
			: reaction_propensity(CalculateReactionPropensity(reaction_rate, volume)), 
			products(products)
		{

		}

		void React()
		{
			for (Layer* product : products)
			{
				product->AddMolecule();
			}
		}

		MoleculeIDs GetProductIDs()
		{
			return product_ids;
		}

		double GetPropensity()
		{
			return reaction_propensity;
		}
	private:
		double reaction_propensity;
		std::vector<Layer*> products;

		double CalculateReactionPropensity(double reaction_rate, double volume)
		{
			return reaction_rate * volume;
		}
	};

	class FirstOrderReaction : public PropensityObject
	{
	public:
		FirstOrderReaction(Layer* reactant, std::vector<Layer*> products, double reaction_rate)
			: reaction_propensity(0), products(products), reaction_rate(reaction_rate)
		{

		}

		void React()
		{
			reactant->RemoveMolecule();
			for (Layer* product : products)
			{
				product->AddMolecule();
			}
		}

		void UpdateReactionPropensity(double molecule_count)
		{
			reaction_propensity = reaction_rate * molecule_count;
		}

		double GetPropensity()
		{
			return reaction_propensity;
		}
	private:
		double reaction_propensity;
		double reaction_rate;
		Layer* reactant;
		std::vector<Layer*> products;
	};

	class SecondOrderReaction : public PropensityObject
	{
	public:
		SecondOrderReaction(Layer* reactant_a, Layer* reactant_b, std::vector<Layer*> products, 
			double reaction_rate, double volume)
			: reaction_factor(reaction_rate / volume), reactant_a(reactant_a), reactant_b(reactant_b),
			is_one_reactant(reactant_a == reactant_b), product_layers(products)
		{

		}

		void React()
		{
			reactant_a->RemoveMolecule();
			reactant_b->RemoveMolecule();
			for (Layer* layer : product_layers)
			{
				layer->AddMolecule();
			}
		}

		void UpdateReactionPropensity()
		{
			reaction_propensity = reactant_a->GetCount() * (reactant_b->GetCount() - is_one_reactant) * reaction_factor;
		}

		double GetPropensity()
		{
			return reaction_propensity;
		}
	private:
		double reaction_propensity;
		double reaction_factor;
		int is_one_reactant;
		Layer* reactant_a;
		Layer* reactant_b;
		std::vector<Layer*> product_layers;
	};

	class Neighbour;

	class PropensityObject
	{
	public:
		virtual double UpdatePropensity() = 0;
	};

	class LinkedPropensityObjects
	{
	public:
		void RequiresUpdate()
		{
			requires_update = true;
		}

		void Add(PropensityObject* object)
		{
			objects.emplace_back(object);
		}

		double UpdatePropensities()
		{
			double delta = 0;
			if (requires_update)
			{
				for (auto& object : objects)
				{
					delta += object->UpdatePropensity();
				}
				requires_update = false;
			}
			return delta;
		}
		
	private:
		bool requires_update;
		std::vector<PropensityObject*> objects;
	};

	// add json log so u can get a list of all propensities
	class Subvolume : public Event2
	{
	public:
		Subvolume(const Vec3d& origin, double length, std::vector<double> diffusion_coefficients)
			: box(origin, Vec3d(length))
		{

		}

		void AddMolecule(MoleculeID molecule_id)
		{
			layers.at(molecule_id).AddMolecule();
		}

		void Run()
		{
			// change event to reaction
			SelectEvent();
			UpdatePropensities();
			// update next event time
			CalculateTimeToNextReaction();
			
			
		}

		void SelectEvent()
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

		const shape::relation::Box& GetBoundingBox() const
		{
			return box;
		}

		// assumes the subvolums are neighbours
		// add IfNeighbourAdd()
		void AddNeighbour(Subvolume& subvolume)
		{
			double diffusion_factor = CalculateDiffusionFactor(subvolume);
			size_t i = 0;
			for (auto& layer : layers)
			{
				layer.AddNeighbourRelationship(&subvolume.GetLayer(i), diffusion_factor);
				i++;
			}
		}

		Layer& GetLayer(MoleculeID id)
		{
			return layers.at(id);
		}

		std::vector<Layer*> GetLayers(MoleculeIDs ids)
		{
			std::vector<Layer*> layer_ptrs;
			layer_ptrs.reserve(ids.size());
			for (auto& id : ids)
			{
				layer_ptrs.emplace_back(&GetLayer(id));
			}
			return layer_ptrs;
		}

		void AddZerothOrderReaction(MoleculeIDs products, double reaction_rate)
		{
			zeroth_order_reactions.emplace_back(GetLayers(products), reaction_rate, GetBoundingBox().CalculateVolume());
			AddLinkToPropensityObjects(products, &zeroth_order_reactions.back());
		}

		void AddFirstOrderReaction(MoleculeID reactant, MoleculeIDs products, double reaction_rate)
		{
			first_order_reactions.emplace_back(GetLayer(reactant), GetLayers(products), reaction_rate);
			AddLinkToPropensityObject(reactant, &first_order_reactions.back());
			AddLinkToPropensityObjects(products, &first_order_reactions.back());
		}

		void AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, MoleculeIDs products, double reaction_rate)
		{
			second_order_reactions.emplace_back(GetLayer(reactant_a), GetLayer(reactant_b), GetLayers(products),
				reaction_rate, GetBoundingBox().CalculateVolume());
			AddLinkToPropensityObjects({ reactant_a, reactant_b }, &second_order_reactions.back());
			AddLinkToPropensityObjects(products, &second_order_reactions.back());
		}

		void AddLinkToPropensityObject(MoleculeID id, PropensityObject* object)
		{
			linked_propensity_objects.at(id)->Add(object);
		}

		void AddLinkToPropensityObjects(MoleculeIDs ids, PropensityObject* object)
		{
			for (MoleculeID id : ids)
			{
				AddLinkToPropensityObject(id, object);
			}
		}

		void UpdatePropensities()
		{
			// only updates the propensity of objects which are affected by a change in molecule count
			for (auto& linked_propensity_object : linked_propensity_objects)
			{
				reaction_propensity += linked_propensity_object->UpdatePropensities();
			}
		}

		double CalculateTimeToNextReaction()
		{
			return -log(Random::GenerateRealUniform()) / reaction_propensity;
		}
	private:
		std::vector<Layer> layers;
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;
		std::vector<SecondOrderReaction> second_order_reactions;
		std::vector<LinkedPropensityObjects*> linked_propensity_objects;
		double reaction_propensity;
		shape::relation::Box box;

		double CalculateDiffusionFactor(const Subvolume& neighbour)
		{
			auto area = GetBoundingBox().CalculateAreaBetweenNeighbouringBoxes(neighbour.GetBoundingBox());
			auto& length1 = GetBoundingBox().GetLength().x;
			auto& length2 = neighbour.GetBoundingBox().GetLength().x;
			return (2 * area) / (std::pow(length1, 3) * (length1 + length2));
		}
	};

	class Region
	{
	public:
		Region(const Vec3d& origin, const Vec3d& length, const Vec3i& n_subvolumes)
			: box(origin, length)
		{

		}

		void CreateSubvolumes(const Vec3i& n_subvolumes)
		{
			subvolumes.reserve(n_subvolumes.Volume());
			Vec3i i;
			for (i.z = 0; i.z < n_subvolumes.z; i.z++)
			{
				for (i.y = 0; i.y < n_subvolumes.y; i.y++)
				{
					for (i.x = 0; i.x < n_subvolumes.x; i.x++)
					{
						Vec3d subvolume_length = box.GetLength() / n_subvolumes;
						subvolumes.emplace_back(box.GetOrigin() + i * subvolume_length, subvolume_length);
					}
				}
			}
		}
	private:
		EventQueue2<Event2> event_queue;
		std::vector<Subvolume> subvolumes;
		shape::relation::Box box;
	};
}