// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_cylinder.h"
#include "relation_circle_surface.h"
#include "relation_shape_3d.h"
#include "relation_rect.h"
#include "axis_3d.h"

// relation checks with flatten won't work for spheres
// must get the position of the cylinder closest to the centre of the sphere per axis,
// then generate the circle of the sphere at the closest point to the centre,

// could pre calculate flattened shapes, which would allow passing references instead of unique pointers
// should do if spheres and boxes end up using same flatenning code

namespace accord
{
	enum class Axis3D;
}

namespace accord::shape::relation
{
	class Shape3D;
	class SufaceShape;
	class CircleSurface;

	class Cylinder : virtual public basic::Cylinder, public Shape3D
	{
	public:
		Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis);

		Cylinder(basic::Cylinder cylinder);

		Cylinder(const CircleSurface& circle_surface);

		Vec3d CalculateNearestPoint(const Vec3d& position) const;

		Vec3d CalculateFurthestPoint(const Vec3d& position) const;

		bool IsOverlapping(const relation::Shape3D& other) const;

		bool IsEnveloping(const relation::Shape3D& other) const;

		bool IsEnvelopedBy(const relation::Shape3D& other) const;

		bool IsOverlapping(const Box& other) const;

		bool IsEnveloping(const Box& other) const;

		bool IsEnvelopedBy(const Box& other) const;

		bool IsOverlapping(const Cylinder& other) const;

		bool IsEnveloping(const Cylinder& other) const;

		bool IsEnvelopedBy(const Cylinder& other) const;

		bool IsOverlapping(const Sphere& other) const;

		bool IsEnveloping(const Sphere& other) const;

		bool IsEnvelopedBy(const Sphere& other) const;

		bool IsPartiallyNeighbouring(const Box& other) const;
		
		bool IsFullyNeighbouring(const Box& other) const;

		// needed for micro-micro and meso-meso relation checking
		// meso-meso requires calculating overlap area as well (what shape calculated overlap area?)
		// meso only requires box overlap checking
		// therefore relation surface only requires is partially neighbouring
		bool IsPartiallyNeighbouring(const Cylinder& other) const;

		// needed for 
		bool IsFullyNeighbouring(const Cylinder& other) const;

		const Shape2D& FlattenInAxis(const Axis3D& axis) const;

		bool IsWithinOrOnBorder(const Vec3d& position) const;

		void ToJson(Json& j) const;

		const Cylinder& GetShape() const;

	private:
		Circle projected_face;
		// projected sides x and y refer to when longitudanal axis of cylinder is along z
		Rect projected_side_x;
		Rect projected_side_y;
		CircleSurface base_face;
		CircleSurface top_face;
	};

	void to_json(Json& j, const Cylinder& shape);
}
