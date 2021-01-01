#pragma once
#include "pch.h"
#include "vec3d.h"
#include "relation_box.h"
#include "object_ids.h"

namespace accord::mesoscopic
{
	class Layer
	{
	public:

		Layer(const Vec3d& origin, double length, double diffusion_coefficient)
			: diffusion_propensity_coefficient(CalculateDiffusionPropensityCoefficient(length, diffusion_coefficient)),
			box(origin, Vec3d(length))
		{

		}

		void AddMolecule()
		{
			molecule_count++;
		}

		void RemoveMolecule()
		{
			molecule_count--;
			if (molecule_count < 0)
			{
				LOG_ERROR("attempting to remove molecule when there are no molecules");
				molecule_count = 0;
			}
		}

		double UpdatePropensity()
		{
			double new_diffusion_propensity = diffusion_propensity_coefficient * molecule_count;
			double delta_propensity = new_diffusion_propensity - diffusion_propensity;
			diffusion_propensity = new_diffusion_propensity;
			return delta_propensity;
		}
	private:
		int molecule_count;
		double diffusion_propensity;
		double diffusion_propensity_coefficient;
		

		double CalculateDiffusionPropensityCoefficient(double length, double diffusion_coefficient)
		{
			return diffusion_coefficient / (length * length);
		}
	};

	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(double reaction_rate, double volume, MoleculeIDs product_ids)
			: reaction_propensity(CalculateReactionPropensity(reaction_rate, volume)), 
			product_ids(product_ids)
		{

		}

		MoleculeIDs GetProductIDs()
		{
			return product_ids;
		}
	private:
		double reaction_propensity;
		MoleculeIDs product_ids;

		double CalculateReactionPropensity(double reaction_rate, double volume)
		{
			return reaction_rate * volume;
		}
	};

	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(double reaction_rate, MoleculeIDs product_ids)
			: reaction_propensity(0), product_ids(product_ids), 
			reaction_rate(reaction_rate)
		{

		}

		MoleculeIDs GetProductIDs()
		{
			return product_ids;
		}

		void UpdateReactionPropensity(double molecule_count)
		{
			reaction_propensity = reaction_rate * molecule_count;
		}
	private:
		double reaction_propensity;
		double reaction_rate;
		MoleculeIDs product_ids;
	};

	class Subvolume
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

		void AddZerothOrderReaction(double reaction_rate, MoleculeIDs product_ids)
		{
			zeroth_order_reactions.emplace_back(reaction_rate, box.CalculateVolume(), product_ids);
		}

		void AddFirstOrderReaction(double reaction_rate, MoleculeID reactant, MoleculeIDs product_ids)
		{
			first_order_reactions.emplace_back(reaction_rate, reactant, product_ids);
		}
	private:
		std::vector<Layer> layers;
		std::vector<ZerothOrderReaction> zeroth_order_reactions;
		std::vector<FirstOrderReaction> first_order_reactions;

		shape::relation::Box box;
	};

	class Region
	{

	};
}