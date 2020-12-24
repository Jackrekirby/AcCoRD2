#include "pch.h"
#include "second_order_reaction.h"

namespace accord
{
	SecondOrderReaction::SecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
		const MoleculeIDs& products, double binding_radius, double unbinding_radius, const RegionIDs& regions)
		: reactant_a(reactant_a), reactant_b(reactant_b), products(products), binding_radius(binding_radius),
		unbinding_radius(unbinding_radius), regions(regions)
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

	const RegionIDs& SecondOrderReaction::GetRegions() const
	{
		return regions;
	}
}