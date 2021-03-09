// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "vec3d.h"
#include "vec2d.h"
#include "axis_3d.h"
#include "basic_shape_3d.h"
#include "basic_box.h"

namespace accord::shape::basic
{
	class CircleSurface;

	class Cylinder : public Shape3D
	{
	public:
		// base_centre = the position at the centre of the negative most base of the cylinder
		// axis = the dimension of the cylinders long axis
		Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis);

		// construct cylinder from a circular surface (length = 0)
		Cylinder(const CircleSurface& circle_surface);

		// create a bounding box around the cylinder
		Box GenerateBoundingBox() const;

		// move the cylinder, in relation to the position of the centre of the negative most base
		void Move(Vec3d base_centre);

		// change the radius of the cylidner
		void SetRadius(double radius);

		// change the length of the cylinder
		void SetLength(double length);

		const Vec3d& GetBaseCentre() const;

		double GetRadius() const;

		// returns the square of the radius
		double GetRadius2() const;

		double GetLength() const;

		// returns the position of the negative most base, along the axial dimension
		double GetBase() const;

		// returns the position of the positive most base, along the axial dimension
		double GetTop() const;

		Axis3D GetAxis() const;

		// get of the 2D position of cylinder as if it has been projected onto a plane
		// perpendicular to its long axis
		Vec2d GetCircleCentre() const;

		double CalculateVolume() const;

		double CalculateSurfaceArea() const;

		// returns true if a point lies on the surface of the cylinder or within it
		// function cannot accurately detect is a point is on the tube of the cylinder due to floating
		// point error, but it can accurately calculate if a point lies on one of the cylinder's bases
		bool IsWithinOrOnBorder(const Vec3d& position) const;

		// retunrs true if a point lies within the surface of the cylinder
		bool IsWithinBorder(const Vec3d& position) const;

		// checks if a point is on either of the cylinder's bases
		bool IsOnFace(const Vec3d& position) const;

		// converts cylinder data to json
		void ToJson(Json& j) const;

		// log cylinder data to output stream
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Cylinder& cylinder)
		{
			return os << fmt::format("base centre = {}, radius = {}, length = {}, axis = {}",
				cylinder.GetBaseCentre(), cylinder.GetRadius(), cylinder.GetLength(),
				cylinder.GetAxis());
		}

	private:
		
		double base; // base = base_centre.GetAxis(axis)
		double length;
		double top; // top = base + length
		double radius;
		double radius2; // radius * radius
		Axis3D axis;
		Vec3d base_centre; // centre of the base (face with smaller position value)
		Vec2d circle_centre; // circle_centre = base_centre.GetPlane(axis)
	};

	// converts cylinder data to json
	void to_json(Json& j, const Cylinder& cylinder);
}