// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "reaction_manager.h"

namespace accord
{
	void ReactionManager::Init(int num_of_molecule_types)
	{
		first_order_reaction_rates_per_molecule_type.reserve(num_of_molecule_types);
		for (int i = 0; i < num_of_molecule_types; i++)
		{
			first_order_reaction_rates_per_molecule_type.emplace_back(0);
		}
	}

	// Zeroth Order Reaction
	void ReactionManager::AddZerothOrderReaction(const std::vector<int>& products, double reaction_rate,
		const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
	{
		zeroth_order_reactions.emplace_back(products, reaction_rate, microscopic_regions, mesoscopic_regions);
	}

	// First Order Reaction
	void ReactionManager::AddFirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products,
		double reaction_rate, const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
	{
		first_order_reactions.emplace_back(reactant, products, reaction_rate, microscopic_regions, mesoscopic_regions);
		first_order_reaction_rates_per_molecule_type.at(reactant) += reaction_rate;
	}

	void ReactionManager::AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b,
		const std::vector<int>& products, double binding_radius, double unbinding_radius,
		double reaction_rate, const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
	{
		second_order_reactions.emplace_back(reactant_a, reactant_b, products, binding_radius, 
			unbinding_radius, reaction_rate, microscopic_regions, mesoscopic_regions);
	}

	void ReactionManager::AddSecondOrderReaction(const MoleculeID& reactant, const std::vector<int>& products,
		double binding_radius, double unbinding_radius, double reaction_rate, 
		const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
	{
		second_order_reactions.emplace_back(reactant, reactant, products, binding_radius,
			unbinding_radius, reaction_rate, microscopic_regions, mesoscopic_regions);
	}

	double ReactionManager::GetSumOfRates(MoleculeID reactant)
	{
		return first_order_reaction_rates_per_molecule_type.at(reactant);
	}

	const std::vector<ZerothOrderReaction>& ReactionManager::GetZerothOrderReactions()
	{
		return zeroth_order_reactions;
	}

	const std::vector<FirstOrderReaction>& ReactionManager::GetFirstOrderReactions()
	{
		return first_order_reactions;
	}

	const std::vector<SecondOrderReaction>& ReactionManager::GetSecondOrderReactions()
	{
		return second_order_reactions;
	}

	std::vector<ZerothOrderReaction> ReactionManager::zeroth_order_reactions;
	std::vector<FirstOrderReaction> ReactionManager::first_order_reactions;
	std::vector<SecondOrderReaction> ReactionManager::second_order_reactions;

	std::vector<double> ReactionManager::first_order_reaction_rates_per_molecule_type;
}