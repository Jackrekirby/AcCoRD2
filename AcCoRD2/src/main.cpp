#include "logger.h"
#include "json.h"
#include "random.h"

#include "logger_test.h"
#include "json_test.h"
#include "random_test.h"
#include "vec_test.h"
#include "output_binary_test.h"

#include "event_queue.h"
#include "event.h"

int main()
{
	accord::Logger::Initialise("logs/debug.txt", "[%^%l%$] %v");

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

	// set run time global Logger level
	//accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	//accord::WriteBinarySingles();
}