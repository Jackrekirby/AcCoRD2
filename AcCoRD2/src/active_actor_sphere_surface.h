#pragma once
#include "active_actor_shape.h"
#include "generating_sphere.h"
#include "relation_sphere.h"

namespace accord
{
	class ActiveActorSphereSurface : public ActiveActorShape, public shape::generating::Sphere, public shape::relation::Sphere
	{
	public:
		ActiveActorSphereSurface(const shape::basic::Sphere& sphere);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}