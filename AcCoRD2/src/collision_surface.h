#pragma once
//#include <memory>
//#include <optional>
#include "collision_3d.h"
#include "abstract_collision_plane_3d.h"
#include "collision_surface_3d_shape.h"

namespace accord::shape::collision
{
	class Surface3D
	{
	public:

		Surface3D(std::unique_ptr<AbstractPlane3D> plane, std::unique_ptr<Surface3DShape> shape);

		std::optional<Collision3D> CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const;
	
		const AbstractPlane3D& GetPlane() const;

		const Surface3DShape& GetShape() const;
	private:
		std::unique_ptr<AbstractPlane3D> plane;
		std::unique_ptr<Surface3DShape> shape;
	};

	void to_json(Json& j, const Surface3D& surface);
}