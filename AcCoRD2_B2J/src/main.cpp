#include "pch.h"
#include "timer.h"
#include "binary_to_json.h"

int main(int argc, char** argv)
{
	// the entry point of the program
	// initialise the logging tool. The log file is created at the .exe location

	accord::Logger::Initialise("log.txt", "[%H:%M:%S.%e] [%^%l%$] %v");
	
	std::string mode;
	#ifdef NDEBUG
		mode = "Release Mode";
		accord::Logger::GetLogger()->set_level(spdlog::level::info);
	#else
		mode = "Debug Mode";
		// switch to trace mode for more detailed debug messages
		accord::Logger::GetLogger()->set_level(spdlog::level::debug);
	#endif
	LOG_INFO("AcCoRD2: Binary To Json Conversion Tool [{}]", mode);

	// convert input arguments to strings
	std::vector<std::string> args(argv, argv + argc);

	accord::Timer timer;
	switch (args.size())
	{
	case 2:
	{
		// only a file / folder passed without a key. Convert that file or all files in a folder and its subfolders.
		// e.g. passing "...\sample1\s1\r0\p0_m0_c.bin" will convert that file only. '...' refers to the absolute path of the relative path
		accord::BinaryToJson::Convert(args.at(1), {});
		break;
	}
	case 3:
	{
		// a folder and a key has been passed as arguments. Convert all files in a folder and its subfolders which match the key.
		// e.g. passing "...\simulation\s1\" "p0" will result in all the files related to passive actors with ID 0 in seed 1 being converted.
		accord::BinaryToJson::Convert(args.at(1), args.at(2));
		break;
	}
	default:
		LOG_WARN("Incorrect number of arguments provided. {} arguments were provided but expected either 2 or 3.", args.size());
		break;
	}

	LOG_INFO("Run time = {}s", timer.Stop());
}