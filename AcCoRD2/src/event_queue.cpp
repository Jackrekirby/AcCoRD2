#include "pch.h"
#include "event_queue.h"

//#include "logger.h"
#include "Event.h"

namespace accord
{
	void EventQueue::Add(Event* event)
	{
		if (events.size() < events.capacity())
		{
			im.emplace_back(events.size());
			pm.emplace_back(events.size());

			events.emplace_back(event);

			Swim(event->queue_index);
		}
		else
		{
			LOG_CRITICAL("Tried to add new Event when EventQueue is at capacity ({})", events.capacity());
			throw std::out_of_range("");
		}
	}

	size_t EventQueue::GetSize()
	{
		return events.size();
	}

	void EventQueue::IncreasePriority(size_t index)
	{
		Swim(im.at(index));
	}

	void EventQueue::DecreasePriority(size_t index)
	{
		Sink(im.at(index));
	}

	Event& EventQueue::Front()
	{
		return *events.at(pm.front());
	}

	EventQueue::EventQueue(size_t capacity)
	{
		events.reserve(capacity);
		pm.reserve(capacity);
		im.reserve(capacity);
	}

	// swaps two heap values in the position map, and updates the inverse map
	void EventQueue::Swap(size_t index_a, size_t index_b)
	{
		std::swap(pm.at(index_a), pm.at(index_b));
		im.at(pm.at(index_a)) = index_a;
		im.at(pm.at(index_b)) = index_b;
	}

	void EventQueue::Swim(size_t index)
	{
		size_t next_index = index / 2;
		while (index > 0 && events.at(pm.at(index))->OccursBefore(*events.at(pm.at(next_index))))
		{
			Swap(index, next_index);
			index = next_index;
			next_index /= 2;
		}
	}

	void EventQueue::Sink(size_t index)
	{
		size_t next_index = index * 2 + 1;
		while (next_index <= pm.size() - 1) {
			// if there are 2 events are the level below then compare them to see which has the highest priority.
			if (next_index < pm.size() - 1 && events.at(pm.at(next_index + 1))->OccursBefore(*events.at(pm.at(next_index))))
			{
				next_index++;
			}
			// compare the highest priority event with the given event to see if they should swap. If not break stop sinking,
			// otherwise swap the events and continue comparing.
			if (events.at(pm.at(index))->OccursBefore(*events.at(pm.at(next_index))))
			{
				break;
			}
			Swap(index, next_index);
			index = next_index;
			next_index = index * 2 + 1;
		}
	}
}