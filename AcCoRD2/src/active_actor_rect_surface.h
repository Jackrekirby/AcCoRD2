// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "active_actor_shape.h"
#include "generating_rect_surface.h"
#include "relation_rect_surface.h"

namespace accord
{
	class ActiveActorRectSurface : public ActiveActorShape, public shape::generating::RectSurface, public shape::relation::RectSurface
	{
	public:
		ActiveActorRectSurface(const shape::basic::RectSurface& rect_surface);

		Vec3d GenerateMolecule();

		double CalculateVolume();

		bool IsOverlapping(const shape::relation::Shape3D& other) const;

		void ToJson(Json& j) const;
	};
}