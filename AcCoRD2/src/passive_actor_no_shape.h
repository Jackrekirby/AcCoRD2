#pragma once
#include "passive_actor_shape.h"

namespace accord
{
	class PassiveActorNoShape : public PassiveActorShape
	{
	public:
		PassiveActorNoShape();

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const;

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const;

		void ToJson(Json& j) const;
	};
}
