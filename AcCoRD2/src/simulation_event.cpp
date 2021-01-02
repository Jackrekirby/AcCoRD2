#include "pch.h"
#include "simulation_event.h"
#include "event_queue2.h"

namespace accord
{
	SimulationEvent::SimulationEvent(double start_time, int priority)
		: Event2(start_time), priority(priority)
	{

	}

	int SimulationEvent::GetPriority() const
	{
		return priority;
	}

	bool SimulationEvent::OccursBefore(const SimulationEvent& other)
	{
		LOG_INFO("time = {}, vs {}", time, other.time);
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

	std::string SimulationEvent::ToString(Type type) {
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
