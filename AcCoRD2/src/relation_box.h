#pragma once
#include "basic_box_3d.h"
#include "relation_box_surface_3d.h"

namespace accord::shape::relation
{
	class Box3D : public basic::Box3D
	{
	public:
		Box3D(Vec3d origin, Vec3d length);

		bool IsOverlapping(const Box3D& other) const;

		bool IsEnveloping(const Box3D& other) const;

		std::optional<Face> IsPartiallyNeighbouring(const Box3D& other) const;

		std::optional<Face> IsFullyNeighbouring(const Box3D& other) const;

		Box3D GenerateOverlapBox(const Box3D& other) const;

		void ToJson(Json& j) const;

		const std::enum_array<Face, BoxSurface3D, 6>& GetFaces() const;
	private:
		std::enum_array<Face, BoxSurface3D, 6> faces;

		std::enum_array<Face, BoxSurface3D, 6> GenerateFaces();

		BoxSurface3D GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
	};
}