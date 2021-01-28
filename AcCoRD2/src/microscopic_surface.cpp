#include "pch.h"
#include "microscopic_surface.h"
#include "microscopic_grid.h"
#include "collision_3d.h"

namespace accord::microscopic
{
	Surface::Surface(std::unique_ptr<SurfaceShape> shape, const SurfaceDirection& surface_direction)
		:shape(std::move(shape)), surface_direction(surface_direction)
	{

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
			//LOG_INFO("Absorbing");
			return std::nullopt;
		case SurfaceType::Membrane:
			return owner->CheckMoleculePath(collision.intersection, end, cycles);
		default:
			LOG_CRITICAL("SurfaceType must be None, Reflecting Or Absorbing");
			throw std::exception();
		}
	}

	const HighPriorityRelative::SurfaceDirection& Surface::GetSurfaceDirection() const
	{
		return surface_direction;
	}

	bool Surface::IsRegion() const
	{
		return false;
	}
}