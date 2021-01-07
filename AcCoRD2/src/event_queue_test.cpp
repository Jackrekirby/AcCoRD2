#include "pch.h"

#include "event_queue_test.h"
//#include "logger.h"
//#include "random.h"
#include "event_queue.h"
#include "event.h"

//#include "event_queue2.h"
//#include "event2.h"
//#include "simulation_event.h"

namespace accord
{
	void EventQueueTest()
	{
		accord::Random::SetSeed();

		//accord::EventQueue event_queue(3);
		//accord::Event event(5.0, 0, &event_queue);
		//accord::Event event2(5.0, 0, &event_queue);
		//accord::Event event3(5.0, 0, &event_queue);

		//LOG_DEBUG(event_queue);
		//event2.UpdateTime(6.0);
		//LOG_DEBUG(event_queue);
		//event3.UpdateTime(5.5);
		//LOG_DEBUG(event_queue);
	}

	//namespace accord
	//{
	//	class TestSimulationEvent : public SimulationEvent
	//	{
	//	public:
	//		TestSimulationEvent(double start_time, int priority = 0)
	//			: SimulationEvent(start_time, priority)
	//		{

	//		}

	//		void Add(EventQueue2<TestSimulationEvent>& event_queue)
	//		{
	//			SetQueueIndex(event_queue.GetSize());
	//			event_queue.Add(this);
	//			this->queue = &event_queue;
	//		}

	//		void UpdateEventTime(double new_time)
	//		{
	//			queue->UpdateEventTime(queue_index, new_time);
	//		}

	//		void Run()
	//		{
	//			LOG_INFO("this is my time = {}", GetEventTime());
	//		}

	//		Type GetType() const
	//		{
	//			return Type::microscopic_region;
	//		}

	//		EventID GetID() const
	//		{
	//			return 69;
	//		}
	//	private:
	//		EventQueue2<TestSimulationEvent>* queue;
	//	};
	//}

	//void Event2Test()
	//{
	//	using namespace accord;
	//	EventQueue2<TestSimulationEvent> q;
	//	q.Reserve(10);
	//	std::vector<TestSimulationEvent> events;
	//	events.emplace_back(5, 1);
	//	events.emplace_back(3, 0);

	//	for (auto& event : events)
	//	{
	//		event.Add(q);
	//	}

	//	LOG_INFO(q.Front());
	//	q.Front().UpdateEventTime(7);
	//	LOG_INFO(q.Front());
	//}


} // namespace accord