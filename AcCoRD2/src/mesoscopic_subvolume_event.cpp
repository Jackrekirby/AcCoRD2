// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "mesoscopic_subvolume_event.h"
#include "subvolume_queue.h"

namespace accord::mesoscopic
{
	SubvolumeEvent::SubvolumeEvent()
		: time(0), queue_index(0), queue(nullptr)
	{

	}

	void SubvolumeEvent::LinkToQueue(SubvolumeQueue* queue, size_t queue_index)
	{
		this->queue = queue;
		this->queue_index = queue_index;
	}

	double SubvolumeEvent::GetTime() const
	{
		return time;
	}

	void SubvolumeEvent::UpdateTime(double delta_time)
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

	void SubvolumeEvent::SetTime(double new_time)
	{
		if (new_time > time)
		{
			//LOG_INFO("increasing time");
			time = new_time;
			queue->DecreasePriority(queue_index);
		}
		else
		{
			//LOG_INFO("decreasing time");
			time = new_time;
			queue->IncreasePriority(queue_index);
		}
	}

	bool SubvolumeEvent::ReactsBefore(const SubvolumeEvent& other)
	{
		if (time == other.time)
		{
			return (Random::GenerateRealUniform() > 0.5);
		}
		return (time < other.time);
	}
}