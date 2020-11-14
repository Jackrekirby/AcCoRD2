#pragma once

namespace accord
{
	class EventQueue;

	class Event
	{
		friend class EventQueue;
	public:
		Event(double start_time, int priority, EventQueue* event_queue);

		void UpdateTime(double new_time);

		double GetTime();

		int GetPriority();

	private:
		double time;
		int priority;
		size_t queue_index;

		EventQueue* event_queue;

		bool OccursBefore(const Event& other);
	};
}
