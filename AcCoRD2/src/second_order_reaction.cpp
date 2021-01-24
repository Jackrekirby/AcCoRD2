#include "pch.h"
#include "second_order_reaction.h"

namespace accord
{
	SecondOrderReaction::SecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b,
		const std::vector<int>& products, double binding_radius, double unbinding_radius, double reaction_rate,
		const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions)
		: reactant_a(reactant_a), reactant_b(reactant_b), products(products), binding_radius(binding_radius),
		unbinding_radius(unbinding_radius), reaction_rate(reaction_rate), microscopic_regions(microscopic_regions), 
		mesoscopic_regions(mesoscopic_regions)
	{
	}

	const MoleculeID& SecondOrderReaction::GetReactantA() const
	{
		return reactant_a;
	}

	const MoleculeID& SecondOrderReaction::GetReactantB() const
	{
		return reactant_b;
	}

	const std::vector<int>& SecondOrderReaction::GetProducts() const
	{
		return products;
	}

	double SecondOrderReaction::GetBindingRadius() const
	{
		return binding_radius;
	}

	double SecondOrderReaction::GetUnBindingRadius() const
	{
		return unbinding_radius;
	}

	double SecondOrderReaction::GetRate() const
	{
		return reaction_rate;
	}

	const MicroscopicRegionIDs& SecondOrderReaction::GetMicroscopicRegions() const
	{
		return microscopic_regions;
	}

	const MesoscopicRegionIDs& SecondOrderReaction::GetMesoscopicRegions() const
	{
		return mesoscopic_regions;
	}
}