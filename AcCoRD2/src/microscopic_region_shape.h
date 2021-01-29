#pragma once
#include "pch.h"
#include "microscopic_surface_shape.h"
#include "basic_shape.h"
#include "microscopic_low_priority_relative_shape.h"

namespace accord
{
	struct Vec3d;
}
// the shape requirements for a microscopic region
namespace accord::microscopic
{
	// could just be a collision shape3D but may require other shape type functionality
	// consider seperating surface shape into one per relationship type
	class RegionShape : public SurfaceShape, public LowPriorityRelativeShape
	{
	public:
		virtual std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		virtual bool IsMoleculeInsideOrOnBorder(const Vec3d& position) const = 0;

		virtual bool IsMoleculeOnBorder(const Vec3d& position) const = 0;

		virtual const shape::basic::Shape3D& GetBasicShape() const = 0;

		virtual Vec3d GenerateMolecule() const = 0;
	};
}
