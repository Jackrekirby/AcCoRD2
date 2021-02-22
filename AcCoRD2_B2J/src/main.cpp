#include "pch.h"
#include "timer.h"
#include "binary_to_json.h"

int main(int argc, char** argv)
{
	// the entry point of the program
	// initialise the logging tool. The log file is created at the .exe location
	
	std::string mode;
	#ifdef NDEBUG
		mode = "Release";
		accord::Logger::Initialise("log.txt", "[%^%l%$] %v");
		accord::Logger::GetLogger()->set_level(spdlog::level::info);
	#else
		mode = "Debug";
		accord::Logger::Initialise("log.txt", "[%H:%M:%S.%e] [%^%l%$] %v");
		// switch to trace mode for more detailed debug messages
		accord::Logger::GetLogger()->set_level(spdlog::level::debug);
	#endif
	
	LOG_INFO("AcCoRD (Actor-based Communication via Reaction-Diffusion)    [{} Mode]", mode);
	LOG_INFO("Version 2.0 (04/02/2021)    Copyright 2021 Jack Kirby. All rights reserved");
	LOG_INFO("Binary To Json Conversion Tool");

	// convert input arguments to strings
	std::vector<std::string> args(argv, argv + argc);

	switch (args.size())
	{
	case 1:
	{
		LOG_INFO("Command Line Arguments:");
		LOG_INFO("[1] AcCoRD2_B2J.exe    (provides information about AcCoRD2_B2J when it is the only argument parsed)");
		LOG_INFO("[2] path               (an absolute file path to a binary file OR a directory path which contains binary files)");
		LOG_INFO("[3] key                (when [2] is a directory, only files whose path partially match the key are converted)");
		LOG_INFO("For example <AcCoRD2_B2J.exe C:/simulation/s1 p0> will result in all the files related to passive actors with ID 0 for seed 1 of the simulation named \"simulation\" being converted from binary to json files.");
		break;
	}
	case 2:
	{
		accord::Timer timer;
		// only a file / folder passed without a key. Convert that file or all files in a folder and its subfolders.
		// e.g. passing "...\sample1\s1\r0\p0_m0_c.bin" will convert that file only. '...' refers to the absolute path of the relative path
		accord::BinaryToJson::Convert(args.at(1), {});
		LOG_INFO("Run time: {}s", timer.Stop());
		break;
	}
	case 3:
	{
		accord::Timer timer;
		// a folder and a key has been passed as arguments. Convert all files in a folder and its subfolders which match the key.
		// e.g. passing "...\simulation\s1\" "p0" will result in all the files related to passive actors with ID 0 in seed 1 being converted.
		accord::BinaryToJson::Convert(args.at(1), args.at(2));
		LOG_INFO("Run time: {}s", timer.Stop());
		break;
	}
	default:
		LOG_ERROR("Exactly {} command line arguments were provided but expected between 1 and 3.", args.size());
		LOG_INFO("[1] AcCoRD2_B2J.exe    (provides information about AcCoRD2_B2J when it is the only argument parsed)");
		LOG_INFO("[2] path               (an absolute file path to a binary file OR a directory path which contains binary files)");
		LOG_INFO("[3] key                (when [2] is a directory, only files whose path partially match the key are converted)");
		LOG_INFO("For example <AcCoRD2_B2J.exe C:/simulation/s1 p0> will result in all the files related to passive actors with ID 0 for seed 1 of the simulation named \"simulation\" being converted from binary to json files.");
		break;
	}
}