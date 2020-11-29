#pragma once
#include "pch.h"

namespace accord::microscopic
{
	using MoleculeID = int;
	class Subvolume2;

	class TypedSubvolume
	{
	public:
		void Add(Subvolume2& subvolume);

		Subvolume2& GetSubvolume(MoleculeID id);

		std::vector<Subvolume2*>& GetSubvolumes();

	private:
		std::vector<Subvolume2*> subvolumes;
	};
}