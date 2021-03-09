// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "generating_cylinder.h"
#include "constants.h"
#include "generating_plane.h"

namespace accord::shape::generating
{
	Cylinder::Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis)
		: basic::Cylinder(base_centre, radius, length, axis),
		base_face({ GetBase(), axis }, { GetCircleCentre(), radius }),
		top_face({ GetTop(), axis }, { GetCircleCentre(), radius }),
		tube(GetCircleCentre(), radius)
	{

	}

	Cylinder::Cylinder(basic::Cylinder cylinder)
		: basic::Cylinder(cylinder),
		tube(GetCircleCentre(), cylinder.GetRadius()),
		base_face({ GetBase(), cylinder.GetAxis() }, { GetCircleCentre(), cylinder.GetRadius() }),
		top_face({ GetTop(), cylinder.GetAxis() }, { GetCircleCentre(), cylinder.GetRadius() })
	{
	}

	Vec3d Cylinder::GeneratePointOnSurface() const
	{
		// generate point on tube (base and top not included)
		return { Random::GenerateRealUniform(GetBase(), GetTop()), tube.GeneratePointOnSurface(), GetAxis() };
	}

	Vec3d Cylinder::GeneratePointInVolume() const
	{
		return { Random::GenerateRealUniform(GetBase(), GetTop()), tube.GeneratePointInArea(), GetAxis() };
	}

	void Cylinder::ToJson(Json& j) const
	{
		j = static_cast<basic::Cylinder>(*this);
	}

}
