#pragma once
//#include <memory>
//#include <optional>
#include "pch.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::shape::collision
{
	class AbstractPlane3D;
	class Surface3DShape;
	class Collision3D;

	class Surface3D
	{
	public:

		Surface3D(std::unique_ptr<AbstractPlane3D> plane, std::unique_ptr<Surface3DShape> shape);

		std::optional<Collision3D> CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		std::optional<Collision3D> CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const;
	
		AbstractPlane3D& GetPlane() const;

		Surface3DShape& GetShape() const;
	private:
		std::unique_ptr<AbstractPlane3D> plane;
		std::unique_ptr<Surface3DShape> shape;
	};

	void to_json(Json& j, const Surface3D& surface);
}