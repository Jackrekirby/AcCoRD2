#pragma once
#include "basic_box.h"
#include "generating_rect_surface.h"

namespace accord::shape::generating
{
	class Box : public basic::Box
	{
	public:
		Box(Vec3d origin, Vec3d length);

		Vec3d GeneratePointOnSurface() const;

		Vec3d GeneratePointInVolume() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Face, RectSurface, 6> faces;

		std::enum_array<Face, RectSurface, 6> GenerateFaces() const;

		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const;
	};
}
