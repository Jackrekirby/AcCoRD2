#include "microscopic_second_order_reaction.h"
#include "pch.h"

namespace accord::microscopic
{
	void SecondOrderReactions::AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products)
	{
		if (reactant_a == reactant_b)
		{
			one_reactant_reactions.emplace_back(reactant_a, products);
		}
		else
		{
			one_reactant_reactions.emplace_back(reactant_a, reactant_b, products);
		}
	}

	OneReactantSecondOrderReaction::OneReactantSecondOrderReaction
	(MoleculeID reactant, const MoleculeIDs& products)
	{

	}

	TwoReactantSecondOrderReaction::TwoReactantSecondOrderReaction
	(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products)
	{

	}
}