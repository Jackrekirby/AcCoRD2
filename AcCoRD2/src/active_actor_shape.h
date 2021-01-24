#pragma once
#include "generating_box.h"
#include "relation_box.h"

namespace accord
{
	namespace shape::relation
	{
		class Shape3D;
	}

	struct Vec3d;
	class ActiveActorShape
	{
	public:
		virtual Vec3d GenerateMolecule() = 0;

		virtual double CalculateVolume() = 0;

		virtual void ToJson(Json& j) const = 0;

		virtual bool IsOverlapping(const shape::relation::Shape3D& other) const = 0;
	};

	//ActiveActorSphere
	//ActiveActorSphereSurface
	//ActiveActorCylinder
	//ActiveActorCylinderSurface
	//ActiveActorRectSurface
	//ActiveActorCircleSurface
	//ActiveActorBoxSurface
	class ActiveActorBox : public ActiveActorShape, public shape::generating::Box, public shape::relation::Box
	{
	public:
		ActiveActorBox(const Vec3d& origin, const Vec3d& length);

		ActiveActorBox(const shape::basic::Box& box);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};

	void to_json(Json& j, const ActiveActorShape& shape);
}