#include "event_queue_test.h"
#include "logger.h"
#include "random.h"
#include "event_queue.h"
#include "event.h"

namespace accord
{
	void EventQueueTest()
	{
		accord::Random::SetSeed();

		accord::EventQueue event_queue(3);
		accord::Event event(5.0, 0, &event_queue);
		accord::Event event2(5.0, 0, &event_queue);
		accord::Event event3(5.0, 0, &event_queue);

		LOG_DEBUG(event_queue);
		event2.UpdateTime(6.0);
		LOG_DEBUG(event_queue);
		event3.UpdateTime(5.5);
		LOG_DEBUG(event_queue);
	}
} // namespace accord