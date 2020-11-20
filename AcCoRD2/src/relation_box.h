#pragma once
#include "basic_box.h"
#include "relation_rect_surface.h"

namespace accord::shape::relation
{
	class Box : public basic::Box
	{
	public:
		Box(Vec3d origin, Vec3d length);

		bool IsOverlapping(const Box& other) const;

		bool IsEnveloping(const Box& other) const;

		std::optional<Face> IsPartiallyNeighbouring(const Box& other) const;

		std::optional<Face> IsFullyNeighbouring(const Box& other) const;

		Box GenerateOverlapBox(const Box& other) const;

		void ToJson(Json& j) const;

		const std::enum_array<Face, RectSurface, 6>& GetFaces() const;
	private:
		std::enum_array<Face, RectSurface, 6> faces;

		std::enum_array<Face, RectSurface, 6> GenerateFaces();

		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
	};
}