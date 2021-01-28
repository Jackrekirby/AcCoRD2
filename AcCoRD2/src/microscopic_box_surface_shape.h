#pragma once
#include "pch.h"
#include "collision_box.h"
#include "generating_box.h"
#include "microscopic_region_shape.h"
#include "microscopic_surface_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class BoxSurfaceShape : public RegionShape, public SurfaceShape, public shape::collision::Box, public shape::generating::Box
	{
	public:
		BoxSurfaceShape(Vec3d origin, Vec3d length);

		BoxSurfaceShape(shape::basic::Box box);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsMoleculeOnBorder(const Vec3d& position) const;

		const shape::basic::Box& GetBasicShape() const;

		void ToJson(Json& j) const;

		Vec3d GenerateMolecule() const;
	};
}
