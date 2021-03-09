// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3d.h"


namespace accord::shape::collision
{
	// hold the collision data between a shape and ray
	// contains the time of intersection, where time = 0 is an intersection at the start of the ray segment, and
	// time = 1 is an intersection a the end of the ray segment. Also holds the intersection point and the reflected point.
	// class is usually wrapped in std::optional so in the case no collision occured null can be returned.
	// An optimisation would be to not calculate the reflected position if its not needed, but is currently always calculated
	class Collision3D
	{
	public:
		double time;
		Vec3d intersection;
		Vec3d reflection;

		Collision3D(double time, Vec3d intersection, Vec3d reflection);

		Collision3D() = default;

		// log the collision data to output stream. Collision must have occurred
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Collision3D& c)
		{
			return os << "time = " << c.time << ", intersection = " << c.intersection << ", reflection = " << c.reflection;
		}

		// log the collision data to the output stream. Collision may or may not have occured
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