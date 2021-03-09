// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "passive_actor_box_shape.h"

namespace accord
{

	PassiveActorBoxShape::PassiveActorBoxShape(shape::basic::Box box)
		: Box(box), shape::basic::Box(box)
	{

	}

	bool PassiveActorBoxShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		return IsWithinBorder(position);
	}

	bool PassiveActorBoxShape::IsSubvolumeInsideBorder(const shape::relation::Box& box) const
	{
		return IsEnveloping(box);
	}

	bool PassiveActorBoxShape::IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const
	{
		bool overlap = IsOverlapping(box);
		// is overlap area very small ignore (floating point error)
		return (overlap && GenerateOverlapBox(box).CalculateVolume() > 1e-17);
	}

	void PassiveActorBoxShape::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Box>(*this);
	}
}
