#pragma once
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

	void to_json(Json& j, const ActiveActorShape& shape);
}