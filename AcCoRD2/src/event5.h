#pragma once

namespace accord
{
	class EventQueue5;

	class Event5
	{
	public:
		Event5(double start_time = 0, int priority = 0);

		void LinkToQueue(EventQueue5* queue, size_t queue_index);

		double GetEventTime() const;

		void SetEventTime(double time);

		void UpdateEventTime(double delta_time);

		bool OccursBefore(const Event5& other);

		virtual std::string LogEvent() const;

		virtual void Run() = 0;

		template<typename OStream>
		friend OStream& operator << (OStream& os, const Event5& event)
		{
			return os << LogEvent();
		}
	protected:
		double time;
		int priority;
		size_t queue_index;
		EventQueue5* queue;
	};
}
