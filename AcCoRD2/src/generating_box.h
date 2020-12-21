#pragma once
#include "basic_box.h"
#include "generating_rect_surface.h"
#include "generating_shape_3d.h"

namespace accord::shape::generating
{
	class Box : virtual public basic::Box, public Shape3D
	{
	public:
		Box(Vec3d origin, Vec3d length);

		Box(basic::Box box);

		Vec3d GeneratePointOnSurface() const;

		Vec3d GeneratePointInVolume() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Face, RectSurface, 6> faces;

		std::enum_array<Face, RectSurface, 6> GenerateFaces() const;

		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const;
	};
}
