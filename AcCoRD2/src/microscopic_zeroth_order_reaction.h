#pragma once
#include "pch.h"

namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products);
	};
}