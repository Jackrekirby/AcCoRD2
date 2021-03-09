// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "basic_plane.h"

namespace accord::shape::relation
{
	class Plane : public basic::Plane
	{
	public:
		Plane(double position, Axis3D axis);

		Plane(basic::Plane plane);

		bool IsNeighbouring(const Plane& other) const;
	};

	void to_json(Json& j, const Plane& plane);
}