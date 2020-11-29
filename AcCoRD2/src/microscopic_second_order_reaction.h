#pragma once
#include "pch.h"
// is it better to pass id's or grids? (can a grid be passed?)

namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	class OneReactantSecondOrderReaction
	{
		OneReactantSecondOrderReaction(MoleculeID reactant, const MoleculeIDs& products);
	};

	class TwoReactantSecondOrderReaction
	{
		TwoReactantSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b, 
			const MoleculeIDs& products);
	};

	class SecondOrderReactions
	{
	public:
		void AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products);
	private:
		std::vector<OneReactantSecondOrderReaction> one_reactant_reactions;
		std::vector<TwoReactantSecondOrderReaction> two_reactant_reactions;
	};
}