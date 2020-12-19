#include "pch.h"
#include "microscopic_cylinder_surface_shape.h"

namespace accord::microscopic
{
	CylinderSurfaceShape::CylinderSurfaceShape(Vec3d base_centre, double radius, double length, Axis3D axis)
		: shape::collision::Cylinder(base_centre, radius, length, axis)
	{

	}

	CylinderSurfaceShape::CylinderSurfaceShape(shape::basic::Cylinder cylinder)
		: shape::collision::Cylinder(cylinder)
	{
	}

	std::optional<shape::collision::Collision3D>
		CylinderSurfaceShape::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Cylinder::CalculateExternalCollisionData(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		CylinderSurfaceShape::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Cylinder::CalculateInternalCollisionData(origin, end);
	}

	bool CylinderSurfaceShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return shape::basic::Cylinder::IsWithinOrOnBorder(position);
	}

	bool CylinderSurfaceShape::IsMoleculeOnBorder(const Vec3d& position) const
	{
		return Cylinder::IsOnFace(position);
	}

	const shape::basic::Cylinder& CylinderSurfaceShape::GetBasicShape() const
	{
		return static_cast<const shape::basic::Cylinder&>(*this);
	}
}
