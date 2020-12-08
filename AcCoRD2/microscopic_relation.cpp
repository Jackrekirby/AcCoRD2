#include "pch.h"
#include "microscopic_relation.h"

namespace accord::shape::collision
{
	class Collision3D;
}
namespace accord
{
	struct Vec3d;
}

namespace accord::microscopic
{
	class Grid2;
	class SurfaceShape;

	Relationship::Relationship(SurfaceType type, Relative* relative)
	{

	}

	SurfaceType Relationship::GetSurfaceType() const
	{
		return type;
	}

	Relative& Relationship::GetRelative() const
	{
		return *relative;
	}
}
