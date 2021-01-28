#pragma once
#include "pch.h"
#include "collision_cylinder.h"
#include "generating_cylinder.h"
#include "microscopic_region_shape.h"
#include "microscopic_surface_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class CylinderSurfaceShape : public RegionShape, public SurfaceShape, public shape::collision::Cylinder, public shape::generating::Cylinder
	{
	public:
		CylinderSurfaceShape(Vec3d base_centre, double radius, double length, Axis3D axis);

		CylinderSurfaceShape(shape::basic::Cylinder cylinder);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		bool IsMoleculeInsideOrOnBorder(const Vec3d& position) const;

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsMoleculeOnBorder(const Vec3d& position) const;

		const shape::basic::Cylinder& GetBasicShape() const;

		void ToJson(Json& j) const;

		Vec3d GenerateMolecule() const;
	};
}
