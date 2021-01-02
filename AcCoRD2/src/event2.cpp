#include "pch.h"
#include "event2.h"
#include "event_queue2.h"

namespace accord
{
	Event2::Event2(double start_time)
		: time(start_time), queue_index(0)
	{
		
	}

	void Event2::SetQueueIndex(size_t queue_index)
	{
		this->queue_index = queue_index;
	}

	double Event2::GetEventTime() const
	{
		return time;
	}

	void Event2::SetEventTime(double time)
	{
		this->time = time;
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
