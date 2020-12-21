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
		// r = curved surface area to flat surface area ratio
		// r = (2 * PI * radius * length) / (2 * PI * radius * radius)
		// r = (length / radius)
		double r = GetLength() / GetRadius();
		double rand = Random::GenerateRealUniform();
		if (rand < r)
		{
			// generate point on tube
			return { Random::GenerateRealUniform(GetBase(), GetTop()), tube.GeneratePointOnSurface(), GetAxis() };
		}
		else if (rand < 0.5 * (1 - r))
		{
			// generate point on base face
			return base_face.GeneratePointOnSurface();
		}
		else
		{
			// generate point on top face
			return base_face.GeneratePointOnSurface();
		}
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
