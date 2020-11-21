#pragma once
//#include "vec3d.h"
#include "basic_box.h"
#include "collision_surface.h"
#include "collision_rect_surface.h"

namespace accord::shape::collision
{
	class Box : public basic::Box
	{
	public:
		Box(Vec3d origin, Vec3d length);

		std::optional<Collision3D> CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end);

		std::optional<Collision3D> CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end);

		const std::enum_array<Face, RectSurface, 6>& GetFaces() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Face, RectSurface, 6> faces;

		std::enum_array<Face, RectSurface, 6> GenerateFaces() const;

		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const;
	};

	void to_json(Json& j, const Box& box);
}
