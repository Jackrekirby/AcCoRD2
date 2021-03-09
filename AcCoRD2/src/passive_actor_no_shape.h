// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "passive_actor_shape.h"

namespace accord
{
	class PassiveActorNoShape : public PassiveActorShape
	{
	public:
		PassiveActorNoShape();

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const;

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const;

		void ToJson(Json& j) const;
	};
}
