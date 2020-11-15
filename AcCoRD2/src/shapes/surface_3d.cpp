#pragma once
#include "surface_3d.h"

#include "collision_3d.h"
#include "abstract_plane_3d.h"
#include "surface_3d_shape.h"

namespace accord::shapes
{
	Surface3D::Surface3D(std::unique_ptr<AbstractPlane3D> plane, std::unique_ptr<Surface3DShape> shape)
		: plane(std::move(plane)), shape(std::move(shape))
	{

	}

	std::optional<Collision3D> Surface3D::CalculateCollisionDataWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end)
	{
		std::optional<double> time = plane->CalculateCollisionTimeWithPositiveFace(origin, end);
		return CalculateIntersectionAndReflection(time, origin, end);
	}

	std::optional<Collision3D> Surface3D::CalculateCollisionDataWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end)
	{
		std::optional<double> time = plane->CalculateCollisionTimeWithNegativeFace(origin, end);
		return CalculateIntersectionAndReflection(time, origin, end);
	}

	std::optional<Collision3D> Surface3D::CalculateIntersectionAndReflection(std::optional<double> time, const math::Vec3d& origin, const math::Vec3d& end)
	{
		if (time.has_value())
		{
			auto intersection = plane->CalculateIntersection(origin, end, time.value());

			if (shape->IsWithinOrOnBorder(intersection.GetPlane(plane->GetAxis())))
			{
				auto reflection = plane->CalculateReflection(intersection, end);
				return Collision3D(time.value(), intersection, reflection);
			}
		}
		return std::nullopt;
	}
}