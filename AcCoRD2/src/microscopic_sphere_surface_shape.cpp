// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "microscopic_sphere_surface_shape.h"

namespace accord::microscopic
{
	SphereSurfaceShape::SphereSurfaceShape(Vec3d centre, double radius)
		: shape::collision::Sphere(centre, radius),
		shape::generating::Sphere(centre, radius),
		shape::basic::Sphere(centre, radius)
	{

	}

	SphereSurfaceShape::SphereSurfaceShape(shape::basic::Sphere sphere)
		: shape::collision::Sphere(sphere),
		shape::generating::Sphere(sphere),
		shape::basic::Sphere(sphere)
	{
	}

	std::optional<shape::collision::Collision3D>
		SphereSurfaceShape::CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Sphere::CalculateExternalCollisionData(origin, end);
	}

	std::optional<shape::collision::Collision3D>
		SphereSurfaceShape::CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
	{
		return shape::collision::Sphere::CalculateInternalCollisionData(origin, end);
	}

	bool SphereSurfaceShape::IsMoleculeInsideOrOnBorder(const Vec3d& position) const
	{
		return shape::basic::Sphere::IsWithinOrOnBorder(position);
	}

	bool SphereSurfaceShape::IsMoleculeInsideBorder(const Vec3d& position) const
	{
		// sphere shape does not have accuracy to check if not on border.
		return shape::basic::Sphere::IsWithinOrOnBorder(position);
	}

	bool SphereSurfaceShape::IsMoleculeOnBorder(const Vec3d& position) const
	{
		LOG_CRITICAL("Sphere's Cannot Be Neighbours, Only High or Low Priority Relations");
		throw std::exception();
	}

	const shape::basic::Sphere& SphereSurfaceShape::GetBasicShape() const
	{
		return static_cast<const shape::basic::Sphere&>(*this);
	}

	void SphereSurfaceShape::ToJson(Json& j) const
	{
		j = GetBasicShape();
	}

	Vec3d SphereSurfaceShape::GenerateMolecule() const
	{
		return shape::generating::Sphere::GeneratePointInVolume();
	}
}
