#pragma once
//#include "vec3d.h"
#include "basic_box.h"
#include "collision_surface.h"

namespace accord::shape::collision
{
	class Box : public basic::Box
	{
	public:
		Box(Vec3d origin, Vec3d length);

		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end);

		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end);

		bool IsWithinBorder(const Vec3d& position) const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;

		bool IsOnBorder(const Vec3d& position) const;

		const std::enum_array<Face, Surface, 6>& GetFaces() const;
	private:
		std::enum_array<Face, Surface, 6> faces;

		std::enum_array<Face, Surface, 6> GenerateFaces() const;
	};

	void to_json(Json& j, const Box& box);
}
