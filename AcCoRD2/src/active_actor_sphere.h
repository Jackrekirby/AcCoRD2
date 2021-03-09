// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "active_actor_shape.h"
#include "generating_sphere.h"
#include "relation_sphere.h"

namespace accord
{
	class ActiveActorSphere : public ActiveActorShape, public shape::generating::Sphere, public shape::relation::Sphere
	{
	public:
		ActiveActorSphere(const shape::basic::Sphere& sphere);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}