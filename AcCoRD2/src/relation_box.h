#pragma once
#include "basic_box.h"
#include "relation_rect_surface.h"
#include "relation_shape_3d.h"

namespace accord::shape::relation
{
	class Box : public basic::Box, public Shape3D
	{
	public:
		Box(Vec3d origin, Vec3d length);

		bool IsOverlapping(const Box& other) const;

		bool IsEnveloping(const Box& other) const;

		bool IsEnvelopedBy(const Box& other) const;


		bool IsOverlapping(const Sphere& other) const;

		bool IsEnveloping(const Sphere& other) const;

		bool IsEnvelopedBy(const Sphere& other) const;


		bool IsOverlapping(const Shape3D& other) const;

		bool IsEnveloping(const Shape3D& other) const;

		bool IsEnvelopedBy(const Shape3D& other) const;

		std::optional<Face> IsPartiallyNeighbouring(const Box& other) const;

		std::optional<Face> IsFullyNeighbouring(const Box& other) const;

		Box GenerateOverlapBox(const Box& other) const;

		Vec3d CalculateNearestPointOnBoundary(const Vec3d& position) const;

		Vec3d CalculateFurthestCornerFromPoint(const Vec3d& position) const;

		void ToJson(Json& j) const;

		const Box& GetShape() const;

		const std::enum_array<Face, RectSurface, 6>& GetFaces() const;
	private:
		std::enum_array<Face, RectSurface, 6> faces;

		std::enum_array<Face, RectSurface, 6> GenerateFaces();

		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
	};

	void to_json(Json& j, const Box& shape);
}