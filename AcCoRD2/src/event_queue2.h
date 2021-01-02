#pragma once
#include "pch.h"

namespace accord
{
	// T is the event class
	template<class T>
	class EventQueue2
	{
	public:
		EventQueue2(size_t capacity)
		{
			events.reserve(capacity);
			pm.reserve(capacity);
			im.reserve(capacity);
		}

		size_t GetSize()
		{
			return events.size();
		}

		void Add(T* event)
		{
			size_t size = GetSize();
			if (size < events.capacity())
			{
				im.emplace_back(size);
				pm.emplace_back(size);

				events.emplace_back(event);

				Swim(size);
			}
			else
			{
				LOG_CRITICAL("Tried to add new Event when EventQueue is at capacity ({})", events.capacity());
				throw std::out_of_range("");
			}
		}

		void UpdateEventTime(size_t queue_index, double new_time)
		{
			if (new_time > GetEvent(queue_index).GetEventTime())
			{
				GetEvent(queue_index).SetEventTime(new_time);
				DecreasePriority(queue_index);
			}
			else
			{
				GetEvent(queue_index).SetEventTime(new_time);
				IncreasePriority(queue_index);
			}
		}

		void IncreasePriority(size_t index)
		{
			Swim(im.at(index));
		}

		void DecreasePriority(size_t index)
		{
			Sink(im.at(index));
		}

		T& Front()
		{
			return GetEvent(pm.front());
		}

		T& GetEvent(size_t index)
		{
			return *(events.at(index));
		}
	private:

		// an unsorted vector which holds pointers to the events
		std::vector<Event3*> events;
		// the position map stores the location of the values as a binary heap
		std::vector<size_t> pm;
		// the inverse map stores the location of the indicies in the position map
		std::vector<size_t> im;

		// swaps two heap values in the position map, and updates the inverse map
		void Swap(size_t index_a, size_t index_b)
		{
			std::swap(pm.at(index_a), pm.at(index_b));
			im.at(pm.at(index_a)) = index_a;
			im.at(pm.at(index_b)) = index_b;
		}

		void Swim(size_t index)
		{
			size_t next_index = index / 2;
			while (index > 0 && GetEvent(pm.at(index)).OccursBefore(GetEvent(pm.at(next_index))))
			{
				Swap(index, next_index);
				index = next_index;
				next_index /= 2;
			}
		}

		void Sink(size_t index)
		{
			size_t next_index = index * 2 + 1;
			while (next_index <= pm.size() - 1) {
				// if there are 2 events are the level below then compare them to see which has the highest priority.
				if (next_index < pm.size() - 1 && GetEvent(pm.at(next_index + 1)).OccursBefore(GetEvent(pm.at(next_index))))
				{
					next_index++;
				}
				// compare the highest priority event with the given event to see if they should swap. If not break stop sinking,
				// otherwise swap the events and continue comparing.
				if (GetEvent(pm.at(index)).OccursBefore(GetEvent(pm.at(next_index))))
				{
					break;
				}
				Swap(index, next_index);
				index = next_index;
				next_index = index * 2 + 1;
			}
		}

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const EventQueue2& event_queue)
		{
			os << "Events (time) = [";
			for (Event3& event : events)
			{
				os << event.GetEventTime() << ", ";
			}
			os << "]\n pm = [";
			for (auto& index : event_queue.pm)
			{
				os << index << ", ";
			}
			os << "]\n im = [";
			for (auto& index : event_queue.im)
			{
				os << index << ", ";
			}
			os << "]";
			return os;
		}
	};
}