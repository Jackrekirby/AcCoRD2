#pragma once
#include "generating_box.h"

namespace accord
{
	struct Vec3d;
	class ActiveActorShape
	{
	public:
		virtual Vec3d GenerateMolecule() = 0;

		virtual double CalculateVolume() = 0;

		virtual void ToJson(Json& j) const = 0;
	};

	//ActiveActorSphere
	//ActiveActorSphereSurface
	//ActiveActorCylinder
	//ActiveActorCylinderSurface
	//ActiveActorRectSurface
	//ActiveActorCircleSurface
	//ActiveActorBoxSurface
	class ActiveActorBox : public ActiveActorShape, public shape::generating::Box
	{
	public:
		ActiveActorBox(const Vec3d& origin, const Vec3d& length);

		ActiveActorBox(const shape::basic::Box& box);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		void ToJson(Json& j) const;
	};

	void to_json(Json& j, const ActiveActorShape& shape);
}