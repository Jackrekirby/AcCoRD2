// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "active_actor_shape.h"
#include "generating_cylinder.h"
#include "relation_cylinder.h"

namespace accord
{
	class ActiveActorCylinderSurface : public ActiveActorShape, public shape::generating::Cylinder, public shape::relation::Cylinder
	{
	public:
		ActiveActorCylinderSurface(const shape::basic::Cylinder& cylinder);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}