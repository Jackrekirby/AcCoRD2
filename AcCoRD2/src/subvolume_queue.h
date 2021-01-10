#pragma once
#include "pch.h"

namespace accord::mesoscopic
{
	class Subvolume;
	class SubvolumeQueue
	{
	public:
		SubvolumeQueue(size_t capacity);

		SubvolumeQueue();

		void Reserve(size_t capacity);

		size_t GetSize();

		void Add(Subvolume* subvolume);

		void UpdateSubvolumeTime(size_t queue_index, double delta_time);

		void SetSubvolumeTime(size_t queue_index, double new_time);

		void IncreasePriority(size_t index);

		void DecreasePriority(size_t index);

		Subvolume& Front();

		Subvolume& GetSubvolume(size_t index);

		std::vector<Subvolume*> GetSubvolumes();
	private:

		// an unsorted vector which holds pointers to the subvolumes
		std::vector<Subvolume*> subvolumes;
		// the position map stores the location of the values as a binary heap
		std::vector<size_t> pm;
		// the inverse map stores the location of the indicies in the position map
		std::vector<size_t> im;

		// swaps two heap values in the position map, and updates the inverse map
		void Swap(size_t index_a, size_t index_b);

		void Swim(size_t index);

		void Sink(size_t index);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const SubvolumeQueue& subvolume_queue)
		{
			os << "pm = [";
			for (auto& index : subvolume_queue.pm)
			{
				os << index << ", ";
			}
			os << "]\n im = [";
			for (auto& index : subvolume_queue.im)
			{
				os << index << ", ";
			}
			os << "]";
			return os;
		}
	};
}