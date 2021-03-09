// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "active_actor_shape.h"
#include "generating_circle_surface.h"
#include "relation_circle_surface.h"

namespace accord
{
	class ActiveActorCircleSurface : public ActiveActorShape, public shape::generating::CircleSurface, public shape::relation::CircleSurface
	{
	public:
		ActiveActorCircleSurface(const shape::basic::CircleSurface& circle_surface);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}