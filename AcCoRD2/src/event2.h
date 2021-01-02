#pragma once
#include "event_queue2.h"

namespace accord
{
	class Event2
	{
	public:
		using EventID = int;

		Event2(double start_time = 0);

		void SetQueueIndex(size_t queue_index);

		double GetEventTime() const;

		void SetEventTime(double time);

		// must be overridden
		virtual void Run() = 0;

		// can be overridden
		virtual bool OccursBefore(const Event2& other);

		template<typename OStream>
		friend OStream& operator << (OStream& os, const Event2& event)
		{
			return os << fmt::format("Time = {}", event.GetEventTime());
		}
	protected:
		double time;
		size_t queue_index;
	};
}
