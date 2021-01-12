#include "pch.h"
#include "second_order_reaction.h"

namespace accord
{
	SecondOrderReaction::SecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
		const MoleculeIDs& products, double binding_radius, double unbinding_radius, double reaction_rate,
		const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions)
		: reactant_a(reactant_a), reactant_b(reactant_b), products(products), binding_radius(binding_radius),
		unbinding_radius(unbinding_radius), reaction_rate(reaction_rate), micro_regions(micro_regions), meso_regions(meso_regions)
	{
	}

	MoleculeID SecondOrderReaction::GetReactantA() const
	{
		return reactant_a;
	}

	MoleculeID SecondOrderReaction::GetReactantB() const
	{
		return reactant_b;
	}

	const MoleculeIDs& SecondOrderReaction::GetProducts() const
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

	const MicroRegionIDs& SecondOrderReaction::GetMicroRegions() const
	{
		return micro_regions;
	}

	const MesoRegionIDs& SecondOrderReaction::GetMesoRegions() const
	{
		return meso_regions;
	}
}