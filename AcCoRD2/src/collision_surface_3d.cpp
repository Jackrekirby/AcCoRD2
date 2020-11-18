#pragma once
#include "collision_surface_3d.h"

#include "collision_3d.h"
#include "abstract_collision_plane_3d.h"
#include "collision_surface_3d_shape.h"

namespace accord::shape::collision
{
	Surface3D::Surface3D(std::unique_ptr<AbstractPlane3D> plane, std::unique_ptr<Surface3DShape> shape)
		: plane(std::move(plane)), shape(std::move(shape))
	{

	}

	std::optional<Collision3D> Surface3D::CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		std::optional<double> time = GetPlane().CalculateCollisionTimeWithPositiveFace(origin, end);
		return CalculateIntersectionAndReflection(time, origin, end);
	}

	std::optional<Collision3D> Surface3D::CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		std::optional<double> time = GetPlane().CalculateCollisionTimeWithNegativeFace(origin, end);
		return CalculateIntersectionAndReflection(time, origin, end);
	}

	std::optional<Collision3D> Surface3D::CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const
	{
		if (time.has_value())
		{
			auto intersection = GetPlane().CalculateIntersection(origin, end, time.value());

			if (GetShape().IsWithinOrOnBorder(intersection.GetPlane(GetPlane().GetAxis())))
			{
				auto reflection = GetPlane().CalculateReflection(intersection, end);
				return Collision3D(time.value(), intersection, reflection);
			}
		}
		return std::nullopt;
	}

	const AbstractPlane3D& Surface3D::GetPlane() const
	{
		return *plane;
	}

	const Surface3DShape& Surface3D::GetShape() const
	{
		return *shape;
	}

	void to_json(Json& j, const Surface3D& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}