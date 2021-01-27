#pragma once
#include "basic_box.h"
#include "relation_rect_surface.h"
#include "relation_shape_3d.h"

namespace accord::shape::relation
{
	class Sphere;
	class Cylinder;

	class Box : virtual public basic::Box, public Shape3D
	{
	public:
		Box(Vec3d origin, Vec3d length);

		Box(basic::Box box);

		Box(const RectSurface& rect_surface);

		bool IsOverlapping(const Box& other) const;

		bool IsEnveloping(const Box& other) const;

		bool IsEnvelopedBy(const Box& other) const;

		bool IsOverlapping(const Sphere& other) const;

		bool IsEnveloping(const Sphere& other) const;

		bool IsEnvelopedBy(const Sphere& other) const;

		bool IsOverlapping(const Cylinder& other) const;

		bool IsEnveloping(const Cylinder& other) const;

		bool IsEnvelopedBy(const Cylinder& other) const;

		bool IsOverlapping(const relation::Shape3D& other) const;

		bool IsEnveloping(const relation::Shape3D& other) const;

		bool IsEnvelopedBy(const relation::Shape3D& other) const;

		bool IsPartiallyNeighbouring(const Box& other) const;

		bool IsFullyNeighbouring(const Box& other) const;

		// requires is partially neighbouring to have been returned true.
		double CalculateAreaBetweenNeighbouringBoxes(const Box& other) const;

		Box GenerateOverlapBox(const Box& other) const;

		Vec3d CalculateNearestPointOnBoundary(const Vec3d& position) const;

		Vec3d CalculateFurthestCornerFromPoint(const Vec3d& position) const;

		const Rect& FlattenInAxis(const Axis3D& axis) const;

		void ToJson(Json& j) const;

		const Box& GetShape() const;

		const std::enum_array<Face, RectSurface, 6>& GetFaces() const;

		const RectSurface& GetFace(Face face) const;
	private:
		std::enum_array<Axis3D, Rect, 3> projected_shapes;

		std::enum_array<Face, RectSurface, 6> faces;

		Rect GenerateProjectedShape(const Axis3D& axis) const;

		std::enum_array<Axis3D, Rect, 3> GenerateProjectedShapes() const;

		std::enum_array<Face, RectSurface, 6> GenerateFaces();

		RectSurface GenerateFace(const Vec3d& position, Axis3D axis, const Vec3d& origin, const Vec3d& end);
	};

	void to_json(Json& j, const Box& shape);
}