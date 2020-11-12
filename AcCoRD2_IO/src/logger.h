#pragma once
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // Compile time log level

#include "spdlog/spdlog.h" // for spdlog::logger
#include "spdlog/fmt/ostr.h" // must be included to log user defined types

#include <memory> // for std::shared_ptr
#include <string> // for std::string

namespace AcCoRD
{
	class Logger
	{
	public:
		static void Initialise(std::string path);
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_logger;
	};
} // namespace AcCoRD

#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)