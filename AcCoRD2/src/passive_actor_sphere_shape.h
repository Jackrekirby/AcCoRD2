#pragma once
#include "passive_actor_shape.h"
#include "relation_sphere.h"

namespace accord
{
	class PassiveActorSphereShape : public PassiveActorShape, shape::relation::Sphere
	{
	public:
		PassiveActorSphereShape(shape::basic::Sphere sphere);

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const;

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const;

		void ToJson(Json& j) const;
	};
}