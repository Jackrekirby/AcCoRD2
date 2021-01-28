#pragma once
#include "active_actor_shape.h"
#include "generating_box.h"
#include "relation_box.h"

namespace accord
{
	class ActiveActorBoxSurface : public ActiveActorShape, public shape::generating::Box, public shape::relation::Box
	{
	public:
		ActiveActorBoxSurface(const Vec3d& origin, const Vec3d& length);

		ActiveActorBoxSurface(const shape::basic::Box& box);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}