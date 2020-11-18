#pragma once
#include "vec3d.h"
//#include <optional>
#include "pch.h"

namespace accord::shape::collision
{
	class Collision3D
	{
	public:
		double time;
		Vec3d intersection;
		Vec3d reflection;

		Collision3D(double time, Vec3d intersection, Vec3d reflection);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Collision3D& c)
		{
			return os << "time = " << c.time << ", intersection = " << c.intersection << ", reflection = " << c.reflection;
		}

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const std::optional<Collision3D>& c)
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