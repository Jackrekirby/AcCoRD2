#include "logger.h"

#include "spdlog/sinks/basic_file_sink.h" // for spdlog::sinks::basic_file_sink_mt
#include "spdlog/sinks/stdout_color_sinks.h" // for spdlog::sinks::stdout_color_sink_mt

#include <iostream> // for std::cout
#include <fstream> // for std::ofstream

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Initialise(std::string file_path, std::string pattern)
{
    // empty the log file and check it can be opened
    std::ofstream ofs(file_path, std::ofstream::out | std::ofstream::trunc);
    if (!ofs)
    {
        std::cout << "[Warning] Logger could not open file <" << file_path << ">" << std::endl;
    }
    ofs.close();

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

        s_Logger = std::make_shared<spdlog::logger>("multi_sink", sink_list.begin(), sink_list.end());
        s_Logger->set_level(spdlog::level::trace);
        // The level of a child sink has priority over the parent sink if it is higher than the parent sink.
        spdlog::set_default_logger(s_Logger);

        SPDLOG_INFO("Logging to <{}>", file_path);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "[Error] Logger initialisation failed: " << ex.what() << std::endl;
    }
}