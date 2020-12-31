#include "pch.h"
#include "active_actor_shape.h"

namespace accord
{
	ActiveActorBox::ActiveActorBox(const Vec3d& origin, const Vec3d& length)
		: shape::generating::Box(origin, length), shape::basic::Box(origin, length)
	{ 

	}

	Vec3d ActiveActorBox::GenerateMolecule()
	{
		return shape::generating::Box::GeneratePointInVolume();
	}

	double ActiveActorBox::CalculateVolume()
	{
		return shape::generating::Box::CalculateVolume();
	}
}