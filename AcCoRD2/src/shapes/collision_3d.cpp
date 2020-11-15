#include "collision_3d.h"

namespace accord::shapes
{
	Collision3D::Collision3D(double time, math::Vec3d intersection, math::Vec3d reflection)
		: time(time), intersection(intersection), reflection(reflection)
	{

	}
}