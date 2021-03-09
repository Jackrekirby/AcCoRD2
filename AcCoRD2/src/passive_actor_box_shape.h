// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "passive_actor_shape.h"
#include "relation_box.h"

namespace accord
{
	class PassiveActorBoxShape : public PassiveActorShape, shape::relation::Box
	{
	public:
		PassiveActorBoxShape(shape::basic::Box box);

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const;

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const;

		void ToJson(Json& j) const;
	};
}