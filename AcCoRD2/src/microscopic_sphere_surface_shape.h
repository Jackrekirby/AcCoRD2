// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"
#include "collision_sphere.h"
#include "generating_sphere.h"
#include "microscopic_region_shape.h"
#include "microscopic_surface_shape.h"

namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class SphereSurfaceShape : public RegionShape, public shape::collision::Sphere, public shape::generating::Sphere
	{
	public:
		SphereSurfaceShape(Vec3d centre, double radius);

		SphereSurfaceShape(shape::basic::Sphere sphere);

		std::optional<shape::collision::Collision3D>
			CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		std::optional<shape::collision::Collision3D>
			CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const;

		bool IsMoleculeInsideOrOnBorder(const Vec3d& position) const;

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsMoleculeOnBorder(const Vec3d& position) const;

		const shape::basic::Sphere& GetBasicShape() const;

		void ToJson(Json& j) const;

		Vec3d GenerateMolecule() const;
	};
}
