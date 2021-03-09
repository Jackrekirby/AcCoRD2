// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "active_actor_shape.h"
#include "generating_box.h"
#include "relation_box.h"

namespace accord
{
	class ActiveActorBox : public ActiveActorShape, public shape::generating::Box, public shape::relation::Box
	{
	public:
		ActiveActorBox(const Vec3d& origin, const Vec3d& length);

		ActiveActorBox(const shape::basic::Box& box);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}