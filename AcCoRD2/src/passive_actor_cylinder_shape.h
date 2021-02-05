#pragma once
#include "passive_actor_shape.h"
#include "relation_cylinder.h"

namespace accord
{
	class PassiveActorCylinderShape : public PassiveActorShape, shape::relation::Cylinder
	{
	public:
		PassiveActorCylinderShape(shape::basic::Cylinder cylinder);

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsSubvolumeInsideBorder(const shape::relation::Box& cylinder) const;

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& cylinder) const;

		void ToJson(Json& j) const;
	};
}