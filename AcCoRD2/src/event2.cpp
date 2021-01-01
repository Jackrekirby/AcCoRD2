#include "pch.h"
#include "event2.h"
#include "event_queue2.h"

namespace accord
{
	Event2::Event2(double start_time)
		: time(start_time), event_queue(nullptr),
		queue_index(0)
	{
		
	}

	void Event2::AddToQueue(EventQueue2<Event2>& event_queue)
	{
		queue_index = event_queue.GetSize();
		this->event_queue = &event_queue;
		event_queue.Add(this);
	}

	double Event2::GetEventTime() const
	{
		return time;
	}

	void Event2::Run()
	{
		LOG_INFO("Event at {}", time);
	}

	void Event2::UpdateEventTime(double new_time)
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

	bool Event2::OccursBefore(const Event2& other)
	{
		if (time == other.time)
		{
			return (Random::GenerateRealUniform() > 0.5);
		}
		return (time < other.time);
	}
}
