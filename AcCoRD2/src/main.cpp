#include "pch.h"
#include "environment.h"
#include "config_importer.h"
#include "timer.h"
#include <regex>

namespace accord
{

	std::string GetDateTime()
	{
		// current date/time based on current system
		time_t now = time(0);
		char c_date_time[26];
		ctime_s(c_date_time, sizeof c_date_time, &now);
		std::string date_time = c_date_time;
		size_t end = date_time.find_last_not_of(" \n\r\t\f\v");
		return (end == std::string::npos) ? "" : date_time.substr(0, end + 1);
	}

	void Run(const std::string& config_filepath, std::optional<uint64_t> seed)
	{
		Timer timer;
		ConfigImporter config(config_filepath, seed);
		Environment::LinkReactionsToRegions();
		Environment::AddEventsToEventQueue();
		LOG_INFO("Build time: {:.3f}s", timer.GetTime());
		timer.Reset();
		LOG_INFO("Starting simulation ({})", GetDateTime());
		Environment::RunSimulation();
		LOG_INFO("Simulation complete ({}). Run Time: {:.3f}s", GetDateTime(), timer.GetTime());
	}
}

//int main()
//{
//	accord::Run("C:/dev/AcCoRD2/configs/simple_micro.json");
//}

int main(int argc, char** argv)
{
	// the entry point of the program
	std::string mode;
	#ifdef NDEBUG
		mode = "Release";
	#else
		mode = "Debug";
	#endif
	std::cout << fmt::format("AcCoRD (Actor-based Communication via Reaction-Diffusion)    [{} Mode]", mode) << std::endl;
	std::cout << fmt::format("Version 2.0 (04/02/2021)    Copyright 2021 Jack Kirby. All rights reserved") << std::endl;
	
	// convert input arguments to strings
	std::vector<std::string> args(argv, argv + argc);

	accord::Timer timer;
	switch (args.size())
	{
	case 1:
	{
		std::cout << fmt::format("Command Line Arguments:") << std::endl;
		std::cout << fmt::format("[1] AcCoRD2.exe    (provides information about AcCoRD when it is the only argument parsed)") << std::endl;
		std::cout << fmt::format("[2] config.json    (an absolute file path to the configuration file)") << std::endl;
		std::cout << fmt::format("[3] seed           (overrides the seed specified in the configuration file)") << std::endl;
		break;
	}
	case 2:
	{
		accord::Run(args.at(1), {});
		break;
	}
	case 3:
	{
		try
		{
			uint64_t seed = std::stoll(args.at(2));
			accord::Run(args.at(1), seed);
		}
		catch (const std::exception&)
		{
			std::cout << fmt::format("[Error] Seed should be of type uint64_t (integer). Command line argument parsed seed with value: {}") << std::endl;
		}
		break;
	}
	default:
		std::cout << fmt::format("[Error] Exactly {} command line arguments were provided but expected between 1 and 3.", args.size()) << std::endl;
		std::cout << fmt::format("Command Line Arguments:") << std::endl;
		std::cout << fmt::format("[1] AcCoRD2.exe    (provides information about AcCoRD when it is the only argument parsed)") << std::endl;
		std::cout << fmt::format("[2] config.json    (an absolute file path to the configuration file)") << std::endl;
		std::cout << fmt::format("[3] seed           (overrides the seed specified in the configuration file)") << std::endl;
		break;
	}
}