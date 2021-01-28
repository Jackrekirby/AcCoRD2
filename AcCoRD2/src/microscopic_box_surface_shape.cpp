#include "pch.h"
#include "microscopic_box_surface_shape.h"

namespace accord::microscopic
{
	BoxSurfaceShape::BoxSurfaceShape(Vec3d origin, Vec3d length)
		: shape::collision::Box(origin, length),
		shape::generating::Box(origin, length),
		shape::basic::Box(origin, length)
	{

	}

	BoxSurfaceShape::BoxSurfaceShape(shape::basic::Box box)
		: shape::collision::Box(box),
		shape::generating::Box(box),
		shape::basic::Box(box)
	{

	}

	std::optional<shape::collision::Collision3D>
		BoxSurfaceShape::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Box::CalculateExternalCollisionData(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		BoxSurfaceShape::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Box::CalculateInternalCollisionData(origin, end);
	}

	bool BoxSurfaceShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return shape::basic::Box::IsWithinBorder(position);
	}

	bool BoxSurfaceShape::IsMoleculeInsideOrOnBorder(const Vec3d& position) const
	{
		return shape::basic::Box::IsWithinOrOnBorder(position);
	}

	bool BoxSurfaceShape::IsMoleculeOnBorder(const Vec3d& position) const
	{
		return shape::basic::Box::IsOnBorder(position);
	}

	const shape::basic::Box& BoxSurfaceShape::GetBasicShape() const
	{
		return static_cast<const shape::basic::Box&>(*this);
	}

	void BoxSurfaceShape::ToJson(Json& j) const
	{
		j = GetBasicShape();
	}

	Vec3d BoxSurfaceShape::GenerateMolecule() const
	{
		return shape::generating::Box::GeneratePointInVolume();
	}
}
