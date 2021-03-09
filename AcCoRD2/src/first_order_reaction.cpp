// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "first_order_reaction.h"
#include "reaction_manager.h"

namespace accord
{
	FirstOrderReaction::FirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products,
		double reaction_rate, const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
		: reactant(reactant), products(products), reaction_rate(reaction_rate),
		microscopic_regions(microscopic_regions), mesoscopic_regions(mesoscopic_regions)
	{

	}

	const MoleculeID& FirstOrderReaction::GetReactant() const
	{
		return reactant;
	}

	const std::vector<int>& FirstOrderReaction::GetProducts() const
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

	const MicroscopicRegionIDs& FirstOrderReaction::GetMicroscopicRegions() const
	{
		return microscopic_regions;
	}

	const MesoscopicRegionIDs& FirstOrderReaction::GetMesoscopicRegions() const
	{
		return mesoscopic_regions;
	}
}