#pragma once
#include "collision_surface.h"

namespace accord::shape::collision
{
	Surface::Surface(std::unique_ptr<AbstractPlane> plane, std::unique_ptr<SurfaceShape> shape)
		: plane(std::move(plane)), shape(std::move(shape))
	{

	}

	std::optional<Collision3D> Surface::CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const
	{
		std::optional<double> time = GetPlane().CalculateCollisionTimeWithPositiveFace(origin, end);
		return CalculateIntersectionAndReflection(time, origin, end);
	}

	std::optional<Collision3D> Surface::CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const
	{
		std::optional<double> time = GetPlane().CalculateCollisionTimeWithNegativeFace(origin, end);
		return CalculateIntersectionAndReflection(time, origin, end);
	}

	std::optional<Collision3D> Surface::CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const
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

	const AbstractPlane& Surface::GetPlane() const
	{
		return *plane;
	}

	const SurfaceShape& Surface::GetShape() const
	{
		return *shape;
	}

	void to_json(Json& j, const Surface& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}