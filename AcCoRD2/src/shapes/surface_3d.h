#pragma once
#include <memory>
#include <optional>

namespace accord::math
{
	struct Vec3d;
}

namespace accord::shapes
{
	class AbstractPlane3D;
	class Surface3DShape;
	class Collision3D;

	class Surface3D
	{
	public:

		Surface3D(std::unique_ptr<AbstractPlane3D> plane, std::unique_ptr<Surface3DShape> shape);

		std::optional<Collision3D> CalculateCollisionDataWithPositiveFace(const math::Vec3d& origin, const math::Vec3d& end);

		std::optional<Collision3D> CalculateCollisionDataWithNegativeFace(const math::Vec3d& origin, const math::Vec3d& end);

		std::optional<Collision3D> CalculateIntersectionAndReflection(std::optional<double> time, const math::Vec3d& origin, const math::Vec3d& end);
	private:
		std::unique_ptr<AbstractPlane3D> plane;
		std::unique_ptr<Surface3DShape> shape;
	};
}