#pragma once
#include "basic_cylinder.h"
#include "relation_circle_surface.h"
#include "relation_shape_3d.h"
#include "axis_3d.h"

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

	class Cylinder : public basic::Cylinder, public Shape3D
	{
	public:
		Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis);

		bool IsOverlapping(const Shape3D& other) const;

		bool IsEnveloping(const Shape3D& other) const;

		bool IsEnvelopedBy(const Shape3D& other) const;

		bool IsOverlapping(const Box& other) const;

		bool IsEnveloping(const Box& other) const;

		bool IsEnvelopedBy(const Box& other) const;


		bool IsOverlapping(const Sphere& other) const;

		bool IsEnveloping(const Sphere& other) const;

		bool IsEnvelopedBy(const Sphere& other) const;

		const SurfaceShape& IsPartiallyNeighbouring(const Box& other) const;
		
		const SurfaceShape& IsFullyNeighbouring(const Box& other) const;

		// needed for micro-micro and meso-meso relation checking
		// meso-meso requires calculating overlap area as well (what shape calculated overlap area?)
		// meso only requires box overlap checking
		// therefore relation surface only requires is partially neighbouring
		const SurfaceShape& IsPartiallyNeighbouring(const Cylinder& other) const;

		// needed for 
		const SurfaceShape& IsFullyNeighbouring(const Cylinder& other) const;

		std::unique_ptr<SurfaceShape> FlattenInAxis(Axis3D axis) const;

		Box GenerateBoundingBox() const;

		void ToJson(Json& j) const;

		const Cylinder& GetShape() const;

	private:
		CircleSurface base_face;
		CircleSurface top_face;
	};

	void to_json(Json& j, const Cylinder& shape);
}
