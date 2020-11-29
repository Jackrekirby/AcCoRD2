#include "microscopic_typed_subvolume.h"

namespace accord::microscopic
{
	void TypedSubvolume::Add(Subvolume2& subvolume)
	{
		subvolumes.emplace_back(&subvolume);
	}

	Subvolume2& TypedSubvolume::GetSubvolume(MoleculeID id)
	{
		return *(subvolumes.at(id));
	}

	std::vector<Subvolume2*>& TypedSubvolume::GetSubvolumes()
	{
		return subvolumes;
	}
}