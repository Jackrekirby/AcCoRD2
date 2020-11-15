#include "pch.h"
//#include "logger.h"
#include "BinaryToJson.h"

int main(int argc, char** argv)
{
	accord::Logger::Initialise("log.txt", "[%H:%M:%S.%e] [%^%l%$] %v");
	LOG_INFO("AcCoRD2 Binary To Json Conversion Tool");

	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	std::vector<std::string> args(argv, argv + argc);

	switch (args.size())
	{
	case 2:
	{
		accord::BinaryToJson::Convert(args.at(1), {});
		break;
	}
	case 3:
	{
		accord::BinaryToJson::Convert(args.at(1), args.at(2));
		break;
	}
	default:
		LOG_WARN("Incorrect number of arguments provided ({})", args.size());
		break;
	}
}