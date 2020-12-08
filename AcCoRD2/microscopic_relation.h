#pragma once
#include "pch.h"
#include "vec3d.h"
#include "molecule_destination.h"

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

	enum class SurfaceType
	{
		Absorping, Adsorbing, Membrane, Reflecting, None
	};

	class Relative
	{
		virtual SurfaceType GetDefaultSurfaceType() const = 0;

		virtual SurfaceShape& GetShape() const = 0;

		virtual std::optional<MoleculeDestination> PassMolecule(const Vec3d& end,
			const shape::collision::Collision3D& collision, Grid2* owner) = 0;
	};

	// relationship contains the attributes of the relationship a pointer to one of the relatives.
	class Relationship
	{
	public:
		Relationship(SurfaceType type, Relative* relative);

		SurfaceType GetSurfaceType() const;

		Relative& GetRelative() const;

	private: 
		SurfaceType type;
		Relative* relative;
	};
}
