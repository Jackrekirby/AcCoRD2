#include "pch.h"
#include "active_actor_shape.h"

namespace accord
{
	void to_json(Json& j, const ActiveActorShape& shape)
	{
		shape.ToJson(j);
	}
}