#include "logger.h"

#include "logger_test.h"

int main()
{
	const std::string DEFAULT_LOG_PATTERN = "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v";
	const std::string NOSOURCE_LOG_PATTERN = "[%H:%M:%S.%e] [%^%l%$] %v";
	const std::string NOTIME_LOG_PATTERN = "[%^%l%$] %s:%# %!() %v";
	const std::string BASIC_LOG_PATTERN = "%v";

	Logger::Initialise("logs/debug.txt", NOSOURCE_LOG_PATTERN);

	// set run time global Logger level
	Logger::GetLogger()->set_level(spdlog::level::debug);

	LOG_INFO("AcCoRD 2");

	AcCoRD::LoggerTest();
}