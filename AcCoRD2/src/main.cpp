#include "logger.h"
#include "json.h"
#include "random.h"

#include "logger_test.h"
#include "json_test.h"
#include "random_test.h"
#include "vec_test.h"
#include "output_binary_test.h"

int main()
{
	AcCoRD::Logger::Initialise("logs/debug.txt");

	// set run time global Logger level
	AcCoRD::Logger::GetLogger()->set_level(spdlog::level::trace);

	//AcCoRD::LoggerTest();
	//AcCoRD::JsonTest();
	//AcCoRD::RandomTest();
	//AcCoRD::VecTest();
	AcCoRD::OutputBinaryTest();
	AcCoRD::OutputBinaryVectorTest();
}