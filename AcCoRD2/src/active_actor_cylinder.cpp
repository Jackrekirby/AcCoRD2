#include "pch.h"
#include "active_actor_cylinder.h"

namespace accord
{
	ActiveActorCylinder::ActiveActorCylinder(const shape::basic::Cylinder& cylinder)
		: shape::generating::Cylinder(cylinder), shape::basic::Cylinder(cylinder), shape::relation::Cylinder(cylinder)
	{
	}

	Vec3d ActiveActorCylinder::GenerateMolecule()
	{
		return shape::generating::Cylinder::GeneratePointInVolume();
	}

	double ActiveActorCylinder::CalculateVolume()
	{
		return shape::generating::Cylinder::CalculateVolume();
	}

	bool ActiveActorCylinder::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Cylinder::IsOverlapping(other);
	}

	void ActiveActorCylinder::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Cylinder>(*this);
	}
}