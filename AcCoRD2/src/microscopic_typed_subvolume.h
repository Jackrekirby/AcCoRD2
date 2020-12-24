#pragma once
#include "pch.h"

namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;

	class Subvolume;

	class TypedSubvolume
	{
	public:
		void Add(Subvolume& subvolume);

		std::vector<Subvolume*>& GetSubvolumes();

	private:
		std::vector<Subvolume*> subvolumes;
	};
}