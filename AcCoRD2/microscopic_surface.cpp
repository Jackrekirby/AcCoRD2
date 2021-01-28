#include "pch.h"
#include "microscopic_surface.h"
#include "microscopic_grid.h"

namespace accord::microscopic
{
	SurfaceType Surface::GetDefaultSurfaceType() const
	{
		return SurfaceType();
	}

	const SurfaceShape& Surface::GetShape() const
	{
		return *shape;
	}

	std::optional<MoleculeDestination> Surface::PassMolecule(const Vec3d& end, const shape::collision::Collision3D& collision, Grid* owner, SurfaceType surface_type, int cycles, bool allowObstructions)
	{
		//Absorbing, Adsorbing, Membrane, Reflecting, None
		switch (surface_type)
		{
		case SurfaceType::None:
			return owner->CheckMoleculePath(collision.intersection, end, cycles);
		case SurfaceType::Reflecting:
			if (!allowObstructions) return std::nullopt;
			return owner->CheckMoleculePath(collision.intersection, collision.reflection, cycles);
		case SurfaceType::Absorbing:
			return std::nullopt;
		default:
			LOG_CRITICAL("SurfaceType must be None, Reflecting Or Absorbing");
			throw std::exception();
		}
	}

	std::vector<Relationship>& Surface::GetNeighbourRelationships()
	{
		// TODO: insert return statement here
	}

	std::vector<Relationship>& Surface::GetLowPriorityRelationships()
	{
		// TODO: insert return statement here
	}

	std::vector<Relationship>& Surface::GetHighPriorityRelationships()
	{
		// TODO: insert return statement here
	}
}