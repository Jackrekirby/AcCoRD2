#pragma once
//#include "vec3d.h"
#include "basic_box_3d.h"
#include "collision_surface_3d.h"

namespace accord::shape::collision
{
	class Box3D : public basic::Box3D
	{
	public:
		Box3D(Vec3d origin, Vec3d length);

		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end);

		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end);

		bool IsWithinBorder(const Vec3d& position) const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;

		bool IsOnBorder(const Vec3d& position) const;

		const std::enum_array<Faces, Surface3D, 6>& GetFaces() const;
	private:
		std::enum_array<Faces, Surface3D, 6> faces;

		std::enum_array<Faces, Surface3D, 6> GenerateFaces() const;
	};

	void to_json(Json& j, const Box3D& box);
}
