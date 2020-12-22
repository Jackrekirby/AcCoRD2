#include "pch.h"
#include "reaction_manager.h"

namespace accord
{
	ZerothOrderReaction::ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions)
		: products(products), reaction_rate(reaction_rate), regions(regions)
	{

	}

	const MoleculeIDs& ZerothOrderReaction::GetProducts() const
	{
		return products;
	}

	double ZerothOrderReaction::GetRate() const
	{
		return reaction_rate;
	}

	const RegionIDs& ZerothOrderReaction::GetRegions() const
	{
		return regions;
	}

	FirstOrderReaction::FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions)
		: reactant(reactant), products(products), reaction_rate(reaction_rate), regions(regions)
	{

	}

	MoleculeID FirstOrderReaction::GetReactant() const
	{
		return reactant;
	}

	const MoleculeIDs& FirstOrderReaction::GetProducts() const
	{
		return products;
	}

	double FirstOrderReaction::GetRate() const
	{
		return reaction_rate;
	}

	double FirstOrderReaction::GetTotalRate() const
	{
		return ReactionManager::GetSumOfRates(reactant);
	}

	const RegionIDs& FirstOrderReaction::GetRegions() const
	{
		return regions;
	}



	void ReactionManager::Init(int num_of_molecule_types)
	{
		first_order_reaction_rates_per_molecule_type.reserve(num_of_molecule_types);
		for (int i = 0; i < num_of_molecule_types; i++)
		{
			first_order_reaction_rates_per_molecule_type.emplace_back(0);
		}
	}

	// Zeroth Order Reaction
	void ReactionManager::AddZerothReaction(const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions)
	{
		zeroth_order_reactions.emplace_back(products, reaction_rate, regions);
	}

	// First Order Reaction
	void ReactionManager::AddFirstReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions)
	{
		first_order_reactions.emplace_back(reactant, products, reaction_rate, regions);
		first_order_reaction_rates_per_molecule_type.at(reactant) += reaction_rate;
	}

	double ReactionManager::GetSumOfRates(MoleculeID reactant)
	{
		return first_order_reaction_rates_per_molecule_type.at(reactant);
	}

	const ZerothOrderReaction& ReactionManager::GetZerothOrderReaction(RegionID id)
	{
		return zeroth_order_reactions.at(id);
	}

	const FirstOrderReaction& ReactionManager::GetFirstOrderReaction(RegionID id)
	{
		return first_order_reactions.at(id);
	}

	const std::vector<ZerothOrderReaction>& ReactionManager::GetZerothOrderReactions()
	{
		return zeroth_order_reactions;
	}

	const std::vector<FirstOrderReaction>& ReactionManager::GetFirstOrderReactions()
	{
		return first_order_reactions;
	}

	std::vector<ZerothOrderReaction> ReactionManager::zeroth_order_reactions;
	std::vector<FirstOrderReaction> ReactionManager::first_order_reactions;
	std::vector<double> ReactionManager::first_order_reaction_rates_per_molecule_type;

}