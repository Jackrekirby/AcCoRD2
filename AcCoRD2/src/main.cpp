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
	accord::Logger::Initialise("logs/debug.txt");

	// set run time global Logger level
	//accord::Logger::GetLogger()->set_level(spdlog::level::trace);

	//accord::LoggerTest();
	//accord::JsonTest();
	//accord::RandomTest();
	//accord::VecTest();
	//accord::OutputBinaryTest();
	//accord::OutputBinaryVectorTest();
	accord::WriteBinarySingles();
}