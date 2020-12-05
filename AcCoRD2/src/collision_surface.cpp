#pragma once
#include "collision_surface.h"

namespace accord::shape::collision
{
	Surface::Surface(std::unique_ptr<AbstractPlane> plane)
		: plane(std::move(plane))
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
			//LOG_INFO("HIT PLANE");
			auto intersection = GetPlane().CalculateIntersection(origin, end, time.value());
			//LOG_INFO("intersection = {}", intersection);
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

	void to_json(Json& j, const Surface& surface)
	{
		j["plane"] = surface.GetPlane();
		j["shape"] = surface.GetShape();
	}
}