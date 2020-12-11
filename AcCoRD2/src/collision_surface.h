#pragma once
#include "collision_3d.h"
#include "collision_plane.h"
#include "collision_surface_shape.h"

namespace accord::shape::collision
{
	class Surface
	{
	public:

		Surface(Plane plane);

		std::optional<Collision3D> CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const;
	
		const Plane& GetPlane() const;

		virtual const SurfaceShape& GetShape() const = 0;
	private:
		Plane plane;
	};

	void to_json(Json& j, const Surface& surface);
}