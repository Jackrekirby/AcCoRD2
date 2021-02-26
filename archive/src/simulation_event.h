#pragma once
#include "event2.h"
namespace accord
{
	class EventQueue;

	class SimulationEvent : public Event2
	{
		friend class EventQueue;
	public:
		using EventID = int;

		SimulationEvent(double start_time, int priority = 0);

		int GetPriority() const;

		virtual void Run() = 0;

		enum class Type
		{
			microscopic_region, mesoscopic_region, active_actor, passive_actor
		};

		virtual Type GetType() const = 0;

		virtual EventID GetID() const = 0;

		static std::string ToString(Type type);

		template<typename OStream>
		static friend OStream& operator << (OStream& os, const Type& type)
		{
			return os << ToString(type);
		}

		template<typename OStream>
		friend OStream& operator << (OStream& os, const SimulationEvent& event)
		{
			return os << fmt::format("Type:{}, ID:{}, Time:{}",
				event.GetType(), event.GetID(), event.GetEventTime());
		}

		bool OccursBefore(const SimulationEvent& other);

	private:
		int priority;
	};
}
