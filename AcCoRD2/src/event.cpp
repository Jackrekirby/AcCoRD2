#include "pch.h"
#include "event.h"
//#include "random.h"
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

	double Event::GetEventTime() const
	{
		return time;
	}

	int Event::GetPriority() const
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

	std::string Event::ToString(Type type) {
		switch (type)
		{
		case Type::microscopic_region:
			return "microscopic region";
		case Type::mesoscopic_region:
			return "mesoscopic region";
		case Type::active_actor:
			return "active actor";
		case Type::passive_actor:
			return "passive actor";
		}
		LOG_CRITICAL("Unknown Event type");
		throw std::exception();
	}
}
