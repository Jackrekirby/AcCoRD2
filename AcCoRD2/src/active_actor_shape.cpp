#include "pch.h"
#include "active_actor_shape.h"

namespace accord
{
	ActiveActorBox::ActiveActorBox(const Vec3d& origin, const Vec3d& length)
		: shape::generating::Box(origin, length), shape::basic::Box(origin, length)
	{ 

	}

	ActiveActorBox::ActiveActorBox(const shape::basic::Box& box)
		: shape::generating::Box(box), shape::basic::Box(box)
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

	void ActiveActorBox::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Box>(*this);
	}

	void to_json(Json& j, const ActiveActorShape& shape)
	{
		shape.ToJson(j);
	}

}