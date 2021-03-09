// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "collision_3d.h"
#include "collision_plane.h"
#include "collision_shape_2d.h"

namespace accord::shape::collision
{
	// collision surface is used to construct collision boxes and cylinders.
	// they are composed of a plane and 2D surface. The plane calculate the collision data
	// then the 2D shape checks if the collision occured within the shape
	class Surface
	{
	public:

		Surface(Plane plane);

		// calculate if a ray crosses a surface from the POSITIVE to NEGATIVE side
		// if the ray does cross the surface it returns time of intersection
		// where time = 0 is at the origin and time = 1 is at the end of the ray segment
		// the 3D collision can be simplified to a 1D collsion
		std::optional<Collision3D> CalculateCollisionDataWithPositiveFace(const Vec3d& origin, const Vec3d& end) const;

		// calculate if a ray crosses a surface from the NEGATIVE to POSITIVE side
		// if the ray does cross the surface it returns time of intersection
		// where time = 0 is at the origin and time = 1 is at the end of the ray segment
		// the 3D collision can be simplified to a 1D collsion
		std::optional<Collision3D> CalculateCollisionDataWithNegativeFace(const Vec3d& origin, const Vec3d& end) const;

		// calculates the intersection point between ray and surface and the reflected point
		std::optional<Collision3D> CalculateIntersectionAndReflection(std::optional<double> time, const Vec3d& origin, const Vec3d& end) const;
	
		const Plane& GetPlane() const;

		virtual const Shape2D& GetShape() const = 0;
	private:
		Plane plane;
	};

	void to_json(Json& j, const Surface& surface);
}