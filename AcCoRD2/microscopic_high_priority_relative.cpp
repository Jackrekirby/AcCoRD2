#include "pch.h"
#include "microscopic_high_priority_relative.h"

namespace accord::microscopic
{
	void from_json(const Json& j, HighPriorityRelative::SurfaceDirection& surface_direction)
	{
		std::string str = j.get<std::string>();
		if (str == "Internal")
		{
			surface_direction = HighPriorityRelative::SurfaceDirection::Internal;
		}
		else if (str == "External")
		{
			surface_direction = HighPriorityRelative::SurfaceDirection::External;
		}
		else if (str == "Both")
		{
			surface_direction = HighPriorityRelative::SurfaceDirection::Both;
		}
		else
		{
			LOG_CRITICAL("Unknown SurfaceDirection string {}", str);
			throw std::exception();
		}
	}
}