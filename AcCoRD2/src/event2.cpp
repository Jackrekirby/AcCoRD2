#include "pch.h"
#include "event2.h"

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

	// should make this private and a friend function for the queue
	void Event2::SetEventTime(double time)
	{
		this->time = time;
	}

	void Event2::UpdateEventTime(double delta_time)
	{
		this->time += delta_time;
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
