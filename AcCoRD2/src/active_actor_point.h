// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "active_actor_shape.h"
#include "vec3d.h"

namespace accord
{
	class ActiveActorPoint : public ActiveActorShape
	{
	public:
		ActiveActorPoint(const Vec3d& origin);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	private:
		Vec3d origin;
	};
}