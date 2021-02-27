#include "pch.h"
#include "logger_test.h"
//#include "logger.h"

namespace accord
{
	// set define SPDLOG_ACTIVE_LEVEL to change which levels display
	void LoggerTest()
	{
		LOG_TRACE("Trace Message Level");
		LOG_DEBUG("Debug Message");
		LOG_INFO("Info Message");
		LOG_WARN("Warn Message");
		LOG_ERROR("Error Message");
		LOG_CRITICAL("Critical Message");
	}
} // namespace accord