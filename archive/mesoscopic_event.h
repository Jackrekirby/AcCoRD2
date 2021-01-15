#pragma once

// by adding event Type it is now specific to environment events
// consider abstracting to seperate into environment and subvolume events

namespace accord
{
	class EventQueue;

	class SimulationEvent
	{
		friend class EventQueue;
	public:
		using EventID = int;

		SimulationEvent(double start_time, EventQueue* event_queue);

		// should rename UpdateEventTime
		void UpdateTime(double new_time);

		double GetEventTime() const;

		virtual void Run() = 0;

		virtual EventID GetID() const = 0;

		template<typename OStream>
		friend OStream& operator << (OStream& os, const SimulationEvent& event)
		{
			return os << fmt::format("Type:{}, ID:{}, Time:{}",
				event.GetType(), event.GetID(), event.GetEventTime());
		}
	private:
		double time;
		size_t queue_index;
		EventQueue* event_queue;

		bool OccursBefore(const SimulationEvent& other);
	};
}
