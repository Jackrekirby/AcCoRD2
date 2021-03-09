// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "active_actor_box.h"

namespace accord
{
	ActiveActorBox::ActiveActorBox(const Vec3d& origin, const Vec3d& length)
		: shape::generating::Box(origin, length), shape::basic::Box(origin, length), shape::relation::Box(origin, length)
	{

	}

	ActiveActorBox::ActiveActorBox(const shape::basic::Box& box)
		: shape::generating::Box(box), shape::basic::Box(box), shape::relation::Box(box)
	{
	}

	Vec3d ActiveActorBox::GenerateMolecule()
	{
		return shape::generating::Box::GeneratePointInVolume();
	}

	double ActiveActorBox::CalculateVolume()
	{
		return shape::generating::Box::CalculateVolume();
	}

	bool ActiveActorBox::IsOverlapping(const shape::relation::Shape3D& other) const
	{
		return shape::relation::Box::IsOverlapping(other);
	}

	void ActiveActorBox::ToJson(Json& j) const
	{
		j = static_cast<shape::basic::Box>(*this);
	}
}