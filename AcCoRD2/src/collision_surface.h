#pragma once
//#include <memory>
//#include <optional>
#include "collision_3d.h"
#include "abstract_collision_plane.h"
#include "collision_surface_shape.h"

namespace accord::shape::collision
{
	class Surface
	{
	public:

		Surface(std::unique_ptr<AbstractPlane> plane, std::unique_ptr<SurfaceShape> shape);

		std::optional<Collision3D> CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const;
	
		const AbstractPlane& GetPlane() const;

		const SurfaceShape& GetShape() const;
	private:
		std::unique_ptr<AbstractPlane> plane;
		std::unique_ptr<SurfaceShape> shape;
	};

	void to_json(Json& j, const Surface& surface);
}