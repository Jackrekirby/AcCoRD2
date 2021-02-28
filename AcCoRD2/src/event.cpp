#include "pch.h"
#include "event.h"
#include "event_queue.h"

namespace accord
{
	Event::Event(double start_time, int priority)
		: time(start_time), queue_index(0), priority(priority), queue(nullptr)
	{

	}

	void Event::LinkToQueue(EventQueue* queue, size_t queue_index)
	{
		this->queue = queue;
		this->queue_index = queue_index;
	}

	double Event::GetEventTime() const
	{
		return time;
	}

	void Event::UpdateEventTime(double delta_time)
	{
		// negative delta time should never occur. Consider removing.
		if (delta_time > 0)
		{
			time += delta_time;
			queue->DecreasePriority(queue_index);
		}
		else
		{
			time += delta_time;
			queue->IncreasePriority(queue_index);
		}
	}

	void Event::SetEventTime(double new_time)
	{
		//LOG_INFO("THIS TIME {}", new_time);
		if (new_time > time)
		{
			time = new_time;
			queue->DecreasePriority(queue_index);
		}
		else
		{
			time = new_time;
			queue->IncreasePriority(queue_index);
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

	std::string Event::LogEvent() const
	{
		return fmt::format("Index:{}, Priority:{}, Time:{}",
			queue_index, priority, time);
	}
}
