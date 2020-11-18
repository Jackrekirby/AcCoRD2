#pragma once
#include "vec3d.h"
#include "basic_box_3d.h"
#include "collision_3d.h"
#include "surface_3d.h"

namespace accord::shape::collision
{
	class Box3D : public basic::Box3D
	{
	public:

		enum class Faces : int
		{
			nx, ny, nz, px, py, pz
		};

		Box3D(Vec3d origin, Vec3d length);

		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end);

		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end);

		bool IsWithinBorder(const Vec3d& position) const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;

		bool IsOnBorder(const Vec3d& position) const;

		const std::array<Surface3D, 6>& GetFaces() const
		{
			return faces;
		}
	private:
		std::array<Surface3D, 6> faces;
	};

	void to_json(Json& j, const Box3D& box);
}
