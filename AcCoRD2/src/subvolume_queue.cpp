#include "pch.h"
#include "subvolume_queue.h"
#include "mesoscopic_subvolume.h"

namespace accord::mesoscopic
{
	SubvolumeQueue::SubvolumeQueue(size_t capacity)
	{
		Reserve(capacity);
	}

	SubvolumeQueue::SubvolumeQueue()
	{

	}

	void SubvolumeQueue::Reserve(size_t capacity)
	{
		subvolumes.reserve(capacity);
		pm.reserve(capacity);
		im.reserve(capacity);
	}

	size_t SubvolumeQueue::GetSize()
	{
		return subvolumes.size();
	}

	void SubvolumeQueue::Add(Subvolume* subvolume)
	{
		size_t size = GetSize();
		if (size < subvolumes.capacity())
		{
			im.emplace_back(size);
			pm.emplace_back(size);

			subvolumes.emplace_back(subvolume);
			subvolume->LinkToQueue(this, size);

			Swim(size);
		}
		else
		{
			LOG_CRITICAL("Tried to add new Subvolume when SubvolumeQueue is at capacity ({})", subvolumes.capacity());
			throw std::out_of_range("");
		}
	}

	void SubvolumeQueue::IncreasePriority(size_t index)
	{
		Swim(im.at(index));
	}

	void SubvolumeQueue::DecreasePriority(size_t index)
	{
		Sink(im.at(index));
	}

	Subvolume& SubvolumeQueue::Front()
	{
		return GetSubvolume(pm.front());
	}

	Subvolume& SubvolumeQueue::GetSubvolume(size_t index)
	{
		return *(subvolumes.at(index));
	}

	std::vector<Subvolume*> SubvolumeQueue::GetSubvolumes()
	{
		return subvolumes;
	}

	void SubvolumeQueue::Swap(size_t index_a, size_t index_b)
	{
		std::swap(pm.at(index_a), pm.at(index_b));
		im.at(pm.at(index_a)) = index_a;
		im.at(pm.at(index_b)) = index_b;
	}

	void SubvolumeQueue::Swim(size_t index)
	{
		size_t next_index = index / 2;
		while (index > 0 && GetSubvolume(pm.at(index)).ReactsBefore(GetSubvolume(pm.at(next_index))))
		{
			Swap(index, next_index);
			index = next_index;
			next_index /= 2;
		}
	}

	void SubvolumeQueue::Sink(size_t index)
	{
		size_t next_index = index * 2 + 1;
		while (next_index <= pm.size() - 1) {
			// if there are 2 subvolumes are the level below then compare them to see which has the highest priority.
			if (next_index < pm.size() - 1 && GetSubvolume(pm.at(next_index + 1)).ReactsBefore(GetSubvolume(pm.at(next_index))))
			{
				next_index++;
			}
			// compare the highest priority subvolume with the given subvolume to see if they should swap. If not break stop sinking,
			// otherwise swap the subvolumes and continue comparing.
			if (GetSubvolume(pm.at(index)).ReactsBefore(GetSubvolume(pm.at(next_index))))
			{
				break;
			}
			Swap(index, next_index);
			index = next_index;
			next_index = index * 2 + 1;
		}
	}
}