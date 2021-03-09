// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "relation_plane.h"
#include "relation_shape_2d.h"

namespace accord::shape::relation
{
	class Surface
	{
	public:
		Surface(Plane plane);

		bool IsPartiallyNeighbouring(const Surface& other) const;

		bool IsFullyNeighbouring(const Surface& other) const;

		const Plane& GetPlane() const;

		virtual const Shape2D& GetShape() const = 0;

	private:
		Plane plane;
	};

	void to_json(Json& j, const Shape2D& surface_shape);
}
