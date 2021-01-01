#pragma once
#include "event_queue2.h"

namespace accord
{
	class Event2
	{
		friend EventQueue2<Event2>;
	public:
		using EventID = int;

		Event2(double start_time = 0);

		void AddToQueue(EventQueue2<Event2>& event_queue);

		void UpdateEventTime(double new_time);

		double GetEventTime() const;

		void Run();
	private:
		double time;
		size_t queue_index;
		EventQueue2<Event2>* event_queue;

		bool OccursBefore(const Event2& other);
	};
}
