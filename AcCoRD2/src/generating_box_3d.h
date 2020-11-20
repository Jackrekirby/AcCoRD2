#pragma once
#include "basic_box_3d.h"
#include "generating_box_surface_3d.h"

namespace accord::shape::generating
{
	class Box3D : public basic::Box3D
	{
	public:
		Box3D(Vec3d origin, Vec3d length);

		Vec3d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Face, BoxSurface3D, 6> faces;

		std::enum_array<Face, BoxSurface3D, 6> GenerateFaces() const;

		BoxSurface3D GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end) const;
	};
}
