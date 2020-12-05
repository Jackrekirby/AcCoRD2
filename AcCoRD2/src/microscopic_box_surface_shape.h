#pragma once
#include "pch.h"
#include "collision_box.h"
#include "microscopic_surface_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class BoxSurfaceShape : public SurfaceShape, public shape::collision::Box
	{
	public:
		BoxSurfaceShape(Vec3d origin, Vec3d length);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsMoleculeOnBorder(const Vec3d& position) const;

		shape::basic::Box GenerateBoundingBox() const;
	};
}
