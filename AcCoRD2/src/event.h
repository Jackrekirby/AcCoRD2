#pragma once

// by adding event Type it is now specific to environment events
// consider abstracting to seperate into environment and subvolume events

namespace accord
{
	class EventQueue;

	class Event
	{
		friend class EventQueue;
	public:
		using EventID = int;

		Event(double start_time, int priority, EventQueue* event_queue);

		// should rename UpdateEventTime
		void UpdateTime(double new_time);

		double GetEventTime() const;

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
		friend OStream& operator << (OStream& os, const Event& event)
		{
			return os << fmt::format("Type:{}, ID:{}, Time:{}", 
				event.GetType(), event.GetID(), event.GetEventTime());
		}
	private:
		double time;
		int priority;
		size_t queue_index;
		EventQueue* event_queue;

		bool OccursBefore(const Event& other);
	};
}
