// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
namespace accord
{
	enum class Axis3D;
	struct Vec3d;
}

namespace accord::shape::relation
{
	class Box;
	class Sphere;
	class Shape2D;
	class Cylinder;

	class Shape3D
	{
	public:
		Shape3D() = default;

		virtual bool IsOverlapping(const Box& other) const = 0;

		virtual bool IsEnveloping(const Box& other) const = 0;

		virtual bool IsEnvelopedBy(const Box& other) const = 0;

		virtual bool IsOverlapping(const Sphere& other) const = 0;

		virtual bool IsEnveloping(const Sphere& other) const = 0;

		virtual bool IsEnvelopedBy(const Sphere& other) const = 0;

		virtual bool IsOverlapping(const Cylinder& other) const = 0;

		virtual bool IsEnveloping(const Cylinder& other) const = 0;

		virtual bool IsEnvelopedBy(const Cylinder& other) const = 0;

		virtual bool IsOverlapping(const Shape3D& other) const = 0;

		virtual bool IsEnveloping(const Shape3D& other) const = 0;

		virtual bool IsEnvelopedBy(const Shape3D& other) const = 0;

		virtual bool IsWithinOrOnBorder(const Vec3d& position) const = 0;

		virtual const Shape2D& FlattenInAxis(const Axis3D& axis) const = 0;

		virtual void ToJson(Json& j) const = 0;

		virtual const Shape3D& GetShape() const = 0;

	};

	void to_json(Json& j, const Shape3D& shape);
}