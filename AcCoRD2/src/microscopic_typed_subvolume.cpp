#include "pch.h"
#include "microscopic_typed_subvolume.h"
#include "microscopic_subvolume2.h"

namespace accord::microscopic
{
	void TypedSubvolume::Add(Subvolume2& subvolume)
	{
		subvolumes.emplace_back(&subvolume);
	}

	std::vector<Subvolume2*>& TypedSubvolume::GetSubvolumes()
	{
		return subvolumes;
	}
}