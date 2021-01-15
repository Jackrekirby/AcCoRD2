#pragma once
#include "event_queue2.h"

namespace accord
{
	namespace mesoscopic
	{
		class Subvolume;
	}

	class MesoscopicEventQueue : public EventQueue2
	{
	public:
		MesoscopicEventQueue(size_t capacity)
			: EventQueue2(capacity)
		{
			events.reserve(capacity);
		}

		mesoscopic::Subvolume& GetEvent(size_t index)
		{
			return *(events.at(index));
		}

		virtual size_t GetEventsCapacity() const
		{
			return events.capacity();
		}

		virtual size_t GetEventsSize() const
		{
			return events.size();
		}
	private:
		std::vector<mesoscopic::Subvolume*> events;
	};
}