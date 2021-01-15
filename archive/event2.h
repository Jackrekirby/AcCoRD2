#pragma once

// while it would be semantically nicer for the user to update the event time in the class instead of to the queue
// as the queue is templatised you cannot pass a derived type of a base class (event) into a templatised class.
// e.g. EventQueue2<&Event2> != EventQueue2<&DerivedClassOfEvent2> 

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

		void UpdateEventTime(double delta_time);

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
