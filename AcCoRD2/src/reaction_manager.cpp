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
	void ReactionManager::AddZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, 
		const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions)
	{
		zeroth_order_reactions.emplace_back(products, reaction_rate, micro_regions, meso_regions);
	}

	// First Order Reaction
	void ReactionManager::AddFirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, 
		double reaction_rate, const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions)
	{
		first_order_reactions.emplace_back(reactant, products, reaction_rate, micro_regions, meso_regions);
		first_order_reaction_rates_per_molecule_type.at(reactant) += reaction_rate;
	}

	void ReactionManager::AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
		const MoleculeIDs& products, double binding_radius, double unbinding_radius, 
		double reaction_rate, const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions)
	{
		second_order_reactions.emplace_back(reactant_a, reactant_b, products, binding_radius, 
			unbinding_radius, reaction_rate, micro_regions, meso_regions);
	}

	void ReactionManager::AddSecondOrderReaction(MoleculeID reactant, const MoleculeIDs& products,
		double binding_radius, double unbinding_radius, double reaction_rate, 
		const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions)
	{
		second_order_reactions.emplace_back(reactant, reactant, products, binding_radius,
			unbinding_radius, reaction_rate, micro_regions, meso_regions);
	}

	double ReactionManager::GetSumOfRates(MoleculeID reactant)
	{
		return first_order_reaction_rates_per_molecule_type.at(reactant);
	}

	const ZerothOrderReaction& ReactionManager::GetZerothOrderReaction(ReactionID id)
	{
		return zeroth_order_reactions.at(id);
	}

	const FirstOrderReaction& ReactionManager::GetFirstOrderReaction(ReactionID id)
	{
		return first_order_reactions.at(id);
	}

	const SecondOrderReaction& ReactionManager::GetSecondOrderReaction(ReactionID id)
	{
		return second_order_reactions.at(id);
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
	std::vector<double> ReactionManager::first_order_reaction_rates_per_molecule_type;
	std::vector<SecondOrderReaction> ReactionManager::second_order_reactions;
}