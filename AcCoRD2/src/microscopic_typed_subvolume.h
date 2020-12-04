#pragma once
#include "pch.h"

namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	class Subvolume2;

	class TypedSubvolume
	{
	public:
		void Add(Subvolume2& subvolume);

		std::vector<Subvolume2*>& GetSubvolumes();

	private:
		std::vector<Subvolume2*> subvolumes;
	};
}