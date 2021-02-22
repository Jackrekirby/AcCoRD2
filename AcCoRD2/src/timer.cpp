#include "pch.h"
#include "timer.h"

namespace accord
{
	Timer::Timer()
	{
		Reset();
	}

	double Timer::GetTime()
	{
		auto end_time_point = std::chrono::high_resolution_clock::now();

		auto start_time = std::chrono::time_point_cast<std::chrono::milliseconds>(start_time_point).time_since_epoch();

		auto end_time = std::chrono::time_point_cast<std::chrono::milliseconds>(end_time_point).time_since_epoch();

		auto duration = end_time - start_time;
		// measure time to the nearest milli second then convert to seconds
		return static_cast<double>(duration.count()) * 0.001;
	}

	void Timer::Reset()
	{
		start_time_point = std::chrono::high_resolution_clock::now();
	}
}