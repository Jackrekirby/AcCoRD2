#include "pch.h"
#include "microscopic_cylinder_surface_shape.h"

namespace accord::microscopic
{
	CylinderSurfaceShape::CylinderSurfaceShape(Vec3d base_centre, double radius, double length, Axis3D axis)
		: shape::collision::Cylinder(base_centre, radius, length, axis)
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

	shape::basic::Box CylinderSurfaceShape::GenerateBoundingBox() const
	{
		Vec3d origin(GetBase(), GetCircleCentre() - GetRadius(), GetAxis());
		Vec3d length(GetLength(), { 2 * GetRadius(), 2 * GetRadius() }, GetAxis());
		return { origin, length };
	}
}
