#include "pch.h"
#include "microscopic_grid2.h"

#include "environment.h"
#include "microscopic_region2.h"

#include "vec3b.h"

#include "collision_3d.h"

#include "microscopic_normal_molecule.h"
#include "microscopic_recent_molecule.h"
#include "microscopic_surface_shape.h"


namespace accord::microscopic
{
	Grid2::Grid2(Vec3d origin, Vec3d length, Vec3i n_subvolumes, double diffision_coefficient, MoleculeID id, Region2* region)
		: box(origin, length), n_subvolumes(n_subvolumes), diffision_coefficient(diffision_coefficient),
		region(region), id(id)
	{
		CreateSubvolumes();
	}

	void Grid2::AddMolecule(const Vec3d& position)
	{
		Vec3i index = Vec3d(n_subvolumes) * ((position - box.GetOrigin()) / box.GetLength());
		GetSubvolume(index).AddMolecule(position);
	}

	void Grid2::AddMolecule(const Vec3d& position, double time)
	{
		Vec3d index = Vec3d(n_subvolumes) * ((position - box.GetOrigin()) / box.GetLength());
		GetSubvolume(index).AddMolecule(position, time);
	}

	void Grid2::DiffuseMolecules()
	{
		for (auto& subvolume : subvolumes)
		{
			// normal molecule list is completed replaced each event instead of deleting molecules which move
			// to a new owner
			std::vector<NormalMolecule> normal_molecules;
			for (auto& molecule : subvolume.GetNormalMolecules())
			{
				std::optional<MoleculeDestination> md = CheckMoleculePath(molecule.GetPosition(), DiffuseMolecule(molecule));
				if (md.has_value())
				{
					// if the owner is the same molecule remains a normal molecule
					if (&(md->GetOwner()) == &static_cast<Owner&>(*this))
					{
						normal_molecules.emplace_back(md->GetPosition());
					}
					// if the owner is the another grid, meso region or adsorbing surface add as recent molecule
					else
					{
						md->GetOwner().AddMolecule(md->GetPosition(), GetRegion().GetNextEventTime());
					}
				}
			}

			for (auto& molecule : subvolume.GetRecentMolecules())
			{
				std::optional<MoleculeDestination> md = CheckMoleculePath(molecule.GetPosition(), DiffuseMolecule(molecule));
				if (md.has_value())
				{
					// if the owner is the same molecule remains a normal molecule
					if (&(md->GetOwner()) == &static_cast<Owner&>(*this))
					{
						normal_molecules.emplace_back(md->GetPosition());
					}
					// if the owner is the another grid, meso region or adsorbing surface add as recent molecule
					else
					{
						md->GetOwner().AddMolecule(md->GetPosition(), GetRegion().GetNextEventTime());
					}
				}
			}

			// replace normal list with new list and clear the recent molecules as all recent molecules are now normal
			subvolume.GetNormalMolecules() = normal_molecules;
			subvolume.GetRecentMolecules().clear();
		}		
	}

	std::optional<MoleculeDestination> Grid2::CheckMoleculePath(const Vec3d& origin, const Vec3d& end)
	{
		// for debugging
		g_json["path3D"].emplace_back(origin);
		g_json["path3D"].emplace_back(end);
		

		// need to add max reflections counter

		Relationship* closest_relationship = nullptr;
		shape::collision::Collision3D closest_collision;
		double shortest_time = 2; // collision time must be between 0 and 1
		for (auto& relationship : high_priority_relationships)
		{
			auto collision = relationship.GetRelative().GetShape().CalculateExternalCollisionData(origin, end);
			if (collision.has_value() && collision->time < shortest_time)
			{
				closest_relationship = &relationship;
				closest_collision = collision.value();
			}
		}
		// if the collision time changed there was a valid collision
		if (closest_relationship != nullptr)
		{
			return closest_relationship->GetRelative().PassMolecule(end, 
				closest_collision, this, closest_relationship->GetSurfaceType());
		}

		auto collision = GetRegion().GetShape().CalculateInternalCollisionData(origin, end);
		if (collision.has_value())
		{
			for (auto& relationship : low_priority_relationships)
			{
				if (relationship.GetRelative().GetShape().IsMoleculeInsideBorder(collision->intersection))
				{
					// assumes you dont have mulitple valid low priority neighbours overlapping
					return relationship.GetRelative().PassMolecule(end, collision.value(), 
						this, relationship.GetSurfaceType());
				}
			}

			// would be good if u could get ids of neighbours
			for (auto& relationship : neighbour_relationships)
			{
				// neighbours must be sorted by youngest and neighbours of the same age must not overlap
				if (relationship.GetRelative().GetShape().IsMoleculeOnBorder(collision->intersection))
				{
					LOG_INFO("HIT NEIGHBOUR");
					return relationship.GetRelative().PassMolecule(end, collision.value(), 
						this, relationship.GetSurfaceType());
				}
			}

			// assume reflection at the moment but will depend on the type of surface
			LOG_INFO("MOLECULE REFLECTED");
			
			// dont need an internal surface relative
			// just specific a simulation boundary region which has to be a low priority relative
			// of all regions. Therefore a region does not need its own surface type
			// the global region cannot have a membrane surface (can be done with simple json file check)
			// disable collision checks on global region?
			return PassMolecule(end, collision.value(), this, GetDefaultSurfaceType());
			//return CheckMoleculePath(collision->intersection, collision->reflection);
		}

		return MoleculeDestination(end, this);
	}

	// dont change old position, create new one.
	Vec3d Grid2::DiffuseMolecule(const NormalMolecule& molecule)
	{
		return { molecule.GetPosition() + 
			std::sqrt(2 * diffision_coefficient * GetRegion().GetTimeStep()) *
			Vec3d::GenerateNormal() };
	}

	// will require envionment time to be updated before event is finished or do environment time + time step
	Vec3d Grid2::DiffuseMolecule(const RecentMolecule& molecule)
	{
		return { molecule.GetPosition() +
			std::sqrt(2 * diffision_coefficient * (Environment::GetTime() - molecule.GetTime())) *
			Vec3d::GenerateNormal() };
	}

	// may need const version
	Region2& Grid2::GetRegion()
	{
		return *region;
	}

	// may need const version
	std::vector<Subvolume2>& Grid2::GetSubvolumes()
	{
		return subvolumes;
	}

	// could be private?
	// may need const version
	// will always return a valid subvolume even if index is for a position outside of subvolume
	Subvolume2& Grid2::GetSubvolume(Vec3i index)
	{
		// if index is below or above index range limit it to within range
		index *= (index < Vec3i(0, 0, 0));
		index.EqualIf((index >= n_subvolumes), n_subvolumes - 1);
		return subvolumes.at(index.x + index.y * n_subvolumes.x + index.z * n_subvolumes.x * n_subvolumes.y);
	}

	// could be private?
	// if index is not valid null will be returned
	Subvolume2* Grid2::GetSubvolumeIfExists(const Vec3i& index)
	{
		if ((index < Vec3i(0, 0, 0)).Any()) return nullptr;
		if ((index >= n_subvolumes).Any()) return nullptr;
		return &subvolumes.at(index.x + index.y * n_subvolumes.x + index.z * n_subvolumes.x * n_subvolumes.y);
	}

	// could be const if you are only linking local subvolumes and not vice versa
	// would be more efficient to do both at same time. Would then require a check to see if regions are already
	// neighbours. Grid is of same molecule type
	void Grid2::LinkGrid(Grid2& grid)
	{
		for (auto& s1 : subvolumes)
		{
			for (auto& s2 : grid.subvolumes)
			{
				s1.Link(s2);
			}
		}
	}

	// Local grids (excluding itself) only need a one way connection while external need a two way connection
	// every cell needs to be checked for overlap due to different cell sizes.
	void Grid2::LinkLocalGrid(Grid2& grid)
	{
		// UNECCESSARY? Let region control local grid linking and just call link grid
	}

	MoleculeID Grid2::GetMoleculeID()
	{
		return id;
	}

	void Grid2::AddNeighbour(Relative* relative, SurfaceType type)
	{
		neighbour_relationships.emplace_back(relative, type);
	}

	void Grid2::AddLowPriorityRelative(Relative* relative, SurfaceType type)
	{
		low_priority_relationships.emplace_back(relative, type);
	}

	void Grid2::AddHighPriorityRelative(Relative* relative, SurfaceType type)
	{
		high_priority_relationships.emplace_back(relative, type);
	}

	// create subvolumes upon class construction
	void Grid2::CreateSubvolumes()
	{
		Vec3i i;
		for (i.z = 0; i.z < n_subvolumes.z; i.z++)
		{
			for (i.y = 0; i.y < n_subvolumes.y; i.y++)
			{
				for (i.x = 0; i.x < n_subvolumes.x; i.x++)
				{
					Vec3d subvolume_length = box.GetLength() / n_subvolumes;
					subvolumes.emplace_back(box.GetOrigin() + i * subvolume_length, subvolume_length, this);
				}
			}
		}
	}

	// go through each subvolume of the same molecule type
	void Grid2::LinkSiblingSubvolumes()
	{
		Vec3i i;
		for (i.z = 0; i.z < n_subvolumes.z; i.z++)
		{
			for (i.y = 0; i.y < n_subvolumes.y; i.y++)
			{
				for (i.x = 0; i.x < n_subvolumes.x; i.x++)
				{
					LinkSiblingSubvolumes(i);
				}
			}
		}
	}

	// for a given cell check the 26 cells surrounding it and link them if they are not already linked
	void Grid2::LinkSiblingSubvolumes(const Vec3i& i)
	{
		// should always be passing a valid subvolume;
		auto subvolume = GetSubvolumeIfExists(i);
		if (subvolume == nullptr)
		{
			LOG_CRITICAL("Index of subvolume is out of range. Index = [{}]", i);
			throw std::exception();
		}

		Vec3i j;
		for (j.z = -1; j.z <= 1; j.z++)
		{
			for (j.y = -1; j.y <= 1; j.y++)
			{
				for (j.x = -1; j.x <= 1; j.x++)
				{
					auto subvolume2 = GetSubvolumeIfExists(i + j);
					if (subvolume2 != nullptr)
					{
						subvolume->LinkSibling(*subvolume2);
					}
				}
			}
		}
	}

	// Inherited Class Functions


	const SurfaceShape& Grid2::GetShape() const
	{
		return region->GetShape();
	}

	// may want a different default surface per molecule type
	SurfaceType Grid2::GetDefaultSurfaceType() const
	{
		return region->GetSurfaceType();
	}

	// the global surface must be absorbing or adsorbing
	// KEEP INTERNAL SURFACE BUT SURFACE PER RELATION IS STILL REQUIRED
	// CAN STILL GET RID OF SURFACE CAN HAVE GET BOUNDARY TYPE AND GET SHAPE
	// internal surface must be reflective, absorbing or adsorbing

	// collision spelt incorrectly
	std::optional<MoleculeDestination> Grid2::PassMolecule(const Vec3d& end, 
		const shape::collision::Collision3D& collision, Grid2* owner,
		SurfaceType surface_type)
	{
		//Absorping, Adsorbing, Membrane, Reflecting, None
		switch (surface_type)
		{
		case SurfaceType::None:
			return CheckMoleculePath(collision.intersection, end);
		case SurfaceType::Reflecting:
			return owner->CheckMoleculePath(collision.intersection, collision.reflection);
		case SurfaceType::Absorbing:
			return std::nullopt;
		default:
			// must throw
			break;
		}
		return std::nullopt;
	}
}