#include "pch.h"
#include "passive_actor_shape.h"

namespace accord
{
	void to_json(Json& j, const PassiveActorShape& shape)
	{
		shape.ToJson(j);
	}
}