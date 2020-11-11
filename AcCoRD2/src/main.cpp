#include "logger.h"
#include "json.h"
#include "random.h"

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

	AcCoRD::Random::SetSeed();

	LOG_INFO(AcCoRD::Random::GenerateRealUniform());
	LOG_INFO(AcCoRD::Random::GenerateExponential(1));
	LOG_INFO(AcCoRD::Random::GenerateIntUniform(0, 100));
	LOG_INFO(AcCoRD::Random::GenerateNormal(0, 1));
	LOG_INFO(AcCoRD::Random::GeneratePoisson(4.7));
	LOG_INFO(AcCoRD::Random::GenerateTriangular());
}