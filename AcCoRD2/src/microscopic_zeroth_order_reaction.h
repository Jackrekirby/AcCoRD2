#pragma once
#include "pch.h"

namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	class ZerothOrderReaction
	{
		ZerothOrderReaction(const MoleculeIDs& products);
	};
}