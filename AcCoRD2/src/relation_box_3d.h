#pragma once
#include "basic_box_3d.h"
#include "relation_surface_3d.h"

namespace accord::shape::relation
{
	class Box3D : public basic::Box3D
	{
	public:
		Box3D(Vec3d origin, Vec3d length);

		bool IsOverlapping(const Box3D& other) const;

		bool IsEnveloping(const Box3D& other) const;

		bool IsPartiallyNeighbouring(const Box3D& other) const;

		bool IsFullyNeighbouring(const Box3D& other) const;

		void ToJson(Json& j) const;

		const std::enum_array<Faces, Surface3D, 6>& GetFaces() const;
	private:
		std::enum_array<Faces, Surface3D, 6> faces;

		std::enum_array<Faces, Surface3D, 6> GenerateFaces();
	};
}