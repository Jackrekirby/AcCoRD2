#include "pch.h"
#include "microscopic_typed_subvolume.h"
#include "microscopic_subvolume.h"

namespace accord::microscopic
{
	void TypedSubvolume::Add(Subvolume& subvolume)
	{
		subvolumes.emplace_back(&subvolume);
	}

	std::vector<Subvolume*>& TypedSubvolume::GetSubvolumes()
	{
		return subvolumes;
	}
}