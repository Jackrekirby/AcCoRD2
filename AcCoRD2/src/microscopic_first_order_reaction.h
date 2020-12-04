#pragma once
#include "pch.h"

namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products);
	};
}