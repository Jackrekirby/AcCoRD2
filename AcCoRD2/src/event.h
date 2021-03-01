#pragma once

namespace accord
{
	class EventQueue;

	class Event
	{
	public:
		Event(double start_time = 0, int priority = 0);

		// used to update the event time before it is added to a queue
		void SetTimeNoUpdate(double time);

		void LinkToQueue(EventQueue* queue, size_t queue_index);

		double GetEventTime() const;

		void SetEventTime(double time);

		void UpdateEventTime(double delta_time);

		bool OccursBefore(const Event& other);

		virtual std::string LogEvent() const;

		virtual void Run() = 0;
	protected:
		double time;
		int priority;
		size_t queue_index;
		EventQueue* queue;
	};
}
