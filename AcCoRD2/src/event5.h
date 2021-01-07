#pragma once

namespace accord
{
	class EventQueue5;

	class Event5
	{
	public:
		using EventID = int;

		Event5(double start_time = 0, int priority = 0);

		void LinkToQueue(EventQueue5* queue, size_t queue_index);

		double GetEventTime() const;

		void SetEventTime(double time);

		void UpdateEventTime(double delta_time);

		bool OccursBefore(const Event5& other);

		enum class Type
		{
			microscopic_region, mesoscopic_region, active_actor, passive_actor
		};

		virtual Type GetType() const = 0;

		virtual EventID GetID() const = 0;

		virtual void Run() = 0;

		static std::string ToString(Type type);

		template<typename OStream>
		static friend OStream& operator << (OStream& os, const Type& type)
		{
			return os << ToString(type);
		}

		template<typename OStream>
		friend OStream& operator << (OStream& os, const Event5& event)
		{
			return os << fmt::format("Type:{}, ID:{}, Time:{}",
				event.GetType(), event.GetID(), event.GetEventTime());
		}
	protected:
		double time;
		int priority;
		size_t queue_index;
		EventQueue5* queue;
	};
}
