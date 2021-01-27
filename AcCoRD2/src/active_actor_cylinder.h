#pragma once
#include "active_actor_shape.h"
#include "generating_cylinder.h"
#include "relation_cylinder.h"

namespace accord
{
	class ActiveActorCylinder : public ActiveActorShape, public shape::generating::Cylinder, public shape::relation::Cylinder
	{
	public:
		ActiveActorCylinder(const shape::basic::Cylinder& cylinder);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}