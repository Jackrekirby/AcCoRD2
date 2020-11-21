#pragma once
#include "vec2d.h"
//#include <optional>

namespace accord::shape::collision
{
	class Collision2D
	{
	public:
		double time;
		Vec2d intersection;
		Vec2d reflection;

		Collision2D(double time, Vec2d intersection, Vec2d reflection);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Collision2D& c)
		{
			return os << "time = " << c.time << ", intersection = " << c.intersection << ", reflection = " << c.reflection;
		}

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const std::optional<Collision2D>& c)
		{
			if (c.has_value())
			{
				return os << c.value();
			}
			else 
			{
				return os << "no collision";
			}
		}
	};
}