#include "pch.h"
#include "collision_2d.h"

namespace accord::shape::collision
{
	Collision2D::Collision2D(double time, Vec2d intersection, Vec2d reflection)
		: time(time), intersection(intersection), reflection(reflection)
	{

	}
}