#include "logger.h"
#include "json.h"

#include "logger_test.h"
#include "json_test.h"


int main()
{
	const std::string DEFAULT_LOG_PATTERN = "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v";
	const std::string NOSOURCE_LOG_PATTERN = "[%H:%M:%S.%e] [%^%l%$] %v";
	const std::string NOTIME_LOG_PATTERN = "[%^%l%$] %s:%# %!() %v";
	const std::string BASIC_LOG_PATTERN = "%v";

	AcCoRD::Logger::Initialise("logs/debug.txt", NOSOURCE_LOG_PATTERN);

	// set run time global Logger level
	AcCoRD::Logger::GetLogger()->set_level(spdlog::level::debug);

	LOG_INFO("AcCoRD 2");

	AcCoRD::LoggerTest();
	AcCoRD::JsonTest();

}