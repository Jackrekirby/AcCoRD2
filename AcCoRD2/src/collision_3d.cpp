#include "collision_3d.h"

namespace accord::shape::collision
{
	Collision3D::Collision3D(double time, Vec3d intersection, Vec3d reflection)
		: time(time), intersection(intersection), reflection(reflection)
	{

	}
}