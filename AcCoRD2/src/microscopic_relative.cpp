#include "pch.h"
#include "microscopic_relative.h"
namespace accord::microscopic
{
	void from_json(const Json& j, Relative::SurfaceDirection& surface_direction)
	{
		std::string str = j.get<std::string>();
		if (str == "Internal")
		{
			surface_direction = Relative::SurfaceDirection::Internal;
		}
		else if (str == "External")
		{
			surface_direction = Relative::SurfaceDirection::External;
		}
		else if (str == "Both")
		{
			surface_direction = Relative::SurfaceDirection::Both;
		}
		else
		{
			LOG_CRITICAL("Unknown SurfaceDirection string {}", str);
			throw std::exception();
		}	
	}
}