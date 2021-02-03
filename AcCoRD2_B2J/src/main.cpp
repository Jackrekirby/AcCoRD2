#include "pch.h"
//#include "logger.h"
#include "BinaryToJson.h"

namespace accord
{
	class Timer
	{
	public:
		Timer()
		{
			start_time_point = std::chrono::high_resolution_clock::now();
		}

		double Stop()
		{
			auto end_time_point = std::chrono::high_resolution_clock::now();

			auto start_time = std::chrono::time_point_cast<std::chrono::milliseconds>(start_time_point).time_since_epoch();

			auto end_time = std::chrono::time_point_cast<std::chrono::milliseconds>(end_time_point).time_since_epoch();

			auto duration = end_time - start_time;
			return static_cast<double>(duration.count()) * 0.001;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
	};
}

int main(int argc, char** argv)
{
	accord::Logger::Initialise("log.txt", "[%H:%M:%S.%e] [%^%l%$] %v");
	LOG_INFO("AcCoRD2 Binary To Json Conversion Tool");

	accord::Logger::GetLogger()->set_level(spdlog::level::info);

	std::vector<std::string> args(argv, argv + argc);

	accord::Timer timer;
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

	LOG_INFO("Run time = {}s", timer.Stop());
}