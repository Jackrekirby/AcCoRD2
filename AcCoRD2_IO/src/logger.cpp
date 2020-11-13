#include "logger.h"

#include "spdlog/sinks/basic_file_sink.h" // for spdlog::sinks::basic_file_sink_mt
#include "spdlog/sinks/stdout_color_sinks.h" // for spdlog::sinks::stdout_color_sink_mt

#include <iostream> // for std::cout
#include <fstream> // for std::ofstream

// DEFAULT_LOG_PATTERN          "[%H:%M:%S.%e] [%^%l%$] %s:%# %!() %v"
// NOSOURCE_LOG_PATTERN         "[%H:%M:%S.%e] [%^%l%$] %v"
// NOTIME_LOG_PATTERN           "[%^%l%$] %s:%# %!() %v"
// NOSOURCEORTIME_LOG_PATTERN   "[%^%l%$] %v"
// BASIC_LOG_PATTERN            "%v"

namespace accord
{
    std::shared_ptr<spdlog::logger> Logger::s_logger;

    void Logger::Initialise(std::string file_path, std::string pattern)
    {
        try
        {
            // create console sink
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::trace);
            console_sink->set_pattern(pattern);

            // create file sink
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path, true);
            file_sink->set_level(spdlog::level::trace);
            file_sink->set_pattern(pattern);

            spdlog::sinks_init_list sink_list = { file_sink, console_sink };

            s_logger = std::make_shared<spdlog::logger>("multi_sink", sink_list.begin(), sink_list.end());
            s_logger->set_level(spdlog::level::trace);
            // The level of a child sink has priority over the parent sink if it is higher than the parent sink.
            spdlog::set_default_logger(s_logger);
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "[Error] Logger initialisation failed: " << ex.what() << std::endl;
        }
    }
} // namespace accord