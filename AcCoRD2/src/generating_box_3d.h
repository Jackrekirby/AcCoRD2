#pragma once
#include "basic_box_3d.h"
#include "generating_surface_3d.h"

namespace accord::shape::generating
{
	class Box3D : public basic::Box3D
	{
	public:
		Box3D(Vec3d origin, Vec3d length);

		Vec3d GeneratePointOnSurface() const;

		void ToJson(Json& j) const;
	private:
		std::enum_array<Faces, Surface3D, 6> faces;

		std::enum_array<Faces, Surface3D, 6> GenerateFaces() const;
	};
}
