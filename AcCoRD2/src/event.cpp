#include "event.h"
#include "random.h"
#include "event_queue.h"

namespace accord
{
	class EventQueue;

	Event::Event(double start_time, int priority, EventQueue* event_queue)
		: time(start_time), priority(priority), event_queue(event_queue), 
		queue_index(event_queue->GetSize())
	{
		event_queue->Add(this);
	}

	double Event::GetTime()
	{
		return time;
	}

	int Event::GetPriority()
	{
		return priority;
	}

	void Event::UpdateTime(double new_time)
	{
		if (new_time > time)
		{
			time = new_time;
			event_queue->DecreasePriority(queue_index);
		}
		else
		{
			time = new_time;
			event_queue->IncreasePriority(queue_index);
		}
	}

	bool Event::OccursBefore(const Event& other)
	{
		if (time == other.time)
		{
			if (priority == other.priority)
			{
				return (Random::GenerateRealUniform() > 0.5);
			}
			return (priority > other.priority);
		}
		return (time < other.time);
	}
}
