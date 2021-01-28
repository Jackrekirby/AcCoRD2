#include "pch.h"
#include "microscopic_grid.h"

#include "environment.h"
#include "microscopic_region.h"

#include "vec3b.h"

#include "collision_3d.h"

#include "microscopic_normal_molecule.h"
#include "microscopic_recent_molecule.h"
#include "microscopic_region_shape.h"


namespace accord::microscopic
{
	Grid::Grid(const Vec3d& origin, const Vec3d& length, const Vec3i& n_subvolumes, double diffision_coefficient, const SurfaceType& surface_type, const MoleculeID& id, Region* region)
		: box(origin, length), n_subvolumes(n_subvolumes), diffision_coefficient(diffision_coefficient), region(region), id(id), surface_type(surface_type),
		surface_direction(HighPriorityRelative::SurfaceDirection::External)
	{
		//LOG_INFO("id = {}", id);
		CreateSubvolumes();
		LinkSiblingSubvolumes();
	}

	void Grid::AddMolecule(const Vec3d& position)
	{
		Vec3i index = Vec3d(n_subvolumes) * ((position - box.GetOrigin()) / box.GetLength());
		GetSubvolume(index).AddMolecule(position);
	}

	void Grid::AddMolecule(const Vec3d& position, double time)
	{
		Vec3d index = Vec3d(n_subvolumes) * ((position - box.GetOrigin()) / box.GetLength());
		GetSubvolume(index).AddMolecule(position, time);
	}

	void Grid::AddMolecule()
	{
		AddMolecule(region->GetShape().GenerateMolecule());
	}

	void Grid::AddMolecule(double time)
	{
		AddMolecule(region->GetShape().GenerateMolecule(), time);
	}

	void Grid::DiffuseMolecules()
	{
		int max_cycles = 20;
		for (auto& subvolume : subvolumes)
		{
			// cannot add normal molecules back into subvolume or would result in loop until molecules are outisde of subvolume.
			// molecules are being repeatedly diffused as if a molecule diffuses into a subvolume which has not yet been computed
			// then a molecule is going to diffuse twice

			// normal molecule list is completed replaced each event instead of deleting molecules which move
			// to a new owner
			std::vector<NormalMolecule>& normal_molecules = subvolume.GetNormalDiffusionMolecules();
			normal_molecules.clear();
			for (auto& molecule : subvolume.GetNormalMolecules())
			{
				std::optional<MoleculeDestination> md = CheckMoleculePath(molecule.GetPosition(), DiffuseMolecule(molecule), max_cycles);
				if (md.has_value())
				{
					//LOG_CRITICAL(md->GetPosition());
					// if the owner is the same molecule remains a normal molecule
					if (&(md->GetOwner()) == &static_cast<Owner&>(*this))
					{
						normal_molecules.emplace_back(md->GetPosition());
					}
					// if the owner is another grid, meso region or adsorbing surface add as recent molecule
					else
					{
						md->GetOwner().AddMolecule(md->GetPosition(), GetRegion().GetNextEventTime());
					}
				}
			}

			std::vector<RecentMolecule> recent_molecules;
			for (auto& molecule : subvolume.GetRecentMolecules())
			{
				if (molecule.GetTime() < region->GetEventTime())
				{
					std::optional<MoleculeDestination> md = CheckMoleculePath(molecule.GetPosition(), DiffuseMolecule(molecule), max_cycles);
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
							// Environment::GetTime() = region->GetTime()
							md->GetOwner().AddMolecule(md->GetPosition(), region->GetEventTime());
							//md->GetOwner().AddMolecule(md->GetPosition(), GetRegion().GetNextEventTime();
						}
					}
				}
				else
				{
					// keep recent molecules who are still ahead of environment time
					recent_molecules.emplace_back(molecule);
				}
			}

			//clear the recent molecules as all recent molecules are now normal
			
			subvolume.GetRecentMolecules() = recent_molecules;
		}		

		//  replace normal list with new list
		for (auto& subvolume : subvolumes)
		{
			subvolume.GetNormalMolecules() = subvolume.GetNormalDiffusionMolecules();
		}
	}

	std::optional<MoleculeDestination> Grid::CheckMoleculePath(const Vec3d& origin, const Vec3d& end, 
		int cycles, bool allowObstructions)
	{
		if (cycles > 0)
		{
			cycles--;
			// for debugging
			//g_json["path3D"].emplace_back(origin);
			//g_json["path3D"].emplace_back(end);

			// membranes could be to high or low or neighbour priority relations. Add membranes before region relations

			// need to add max reflections counter

			HighPriorityRelationship* closest_relationship = nullptr;
			shape::collision::Collision3D closest_collision;
			double shortest_time = 2; // collision time must be between 0 and 1
			SurfaceType surface_type = SurfaceType::None;
			int i = 0;
			for (auto& relationship : high_priority_relationships)
			{
				auto& relative = relationship.GetHighPriorityRelative();
				std::optional<shape::collision::Collision3D> collision;
				switch (relative.GetSurfaceDirection())
				{
				case HighPriorityRelative::SurfaceDirection::Internal:
					collision = relative.GetShape().CalculateInternalCollisionData(origin, end);
					break;
				case HighPriorityRelative::SurfaceDirection::External:
					collision = relative.GetShape().CalculateExternalCollisionData(origin, end);
					break;
				case HighPriorityRelative::SurfaceDirection::Both:
					collision = relative.GetShape().CalculateExternalCollisionData(origin, end);
					if (!collision.has_value())
					{
						collision = relative.GetShape().CalculateInternalCollisionData(origin, end);
					}
					break;
				}
				// what if the region has a default membrane surface?
				if (collision.has_value())
				{
					if (collision->time < shortest_time)
					{
						surface_type = relationship.GetSurfaceType();
						closest_relationship = &relationship;
						closest_collision = collision.value();
						shortest_time = collision->time;
					}
					else if (collision->time == shortest_time)
					{
						//LOG_INFO("Same time!");
						if (relationship.GetSurfaceType() == SurfaceType::Membrane)
						{
							surface_type = SurfaceType::Membrane;
						}
						else
						{
							closest_relationship = &relationship;
							closest_collision = collision.value();
						}
					}
				}
			}

			// if the collision time changed there was a valid collision
			if (closest_relationship != nullptr)
			{
				return closest_relationship->GetHighPriorityRelative().PassMolecule(end,
					closest_collision, this, surface_type, cycles, allowObstructions);
			}

			auto collision = GetRegion().GetShape().CalculateInternalCollisionData(origin, end);
			bool passes_through_membrane = false;
			if (collision.has_value())
			{
				// would be good if u could get ids of neighbours
				for (auto& relationship : neighbour_relationships)
				{
					auto& relative = relationship.GetNeighbourRelative();
					// neighbours must be sorted by youngest and neighbours of the same age must not overlap
					if (relative.GetShape().IsMoleculeOnBorder(collision->intersection))
					{
						if (relative.IsRegion())
						{
							if (!passes_through_membrane)
							{
								surface_type = relationship.GetSurfaceType();
							} // else surface type = membrane
							return relative.PassMolecule(end, collision.value(), this, surface_type, cycles, allowObstructions);
						}
						else
						{
							surface_type = relationship.GetSurfaceType();
							if (surface_type != SurfaceType::Membrane)
							{
								return relative.PassMolecule(end, collision.value(), this, surface_type, cycles, allowObstructions);
							}
							passes_through_membrane = true;
						}
					}
				}

				for (auto& relationship : low_priority_relationships)
				{
					if (relationship.GetLowPriorityRelative().GetShape().IsMoleculeInsideBorder(collision->intersection))
					{
						if (!passes_through_membrane)
						{
							surface_type = relationship.GetSurfaceType();
						} // else surface type = membrane
						// assumes you dont have mulitple valid low priority neighbours overlapping
						return relationship.GetLowPriorityRelative().PassMolecule(end, collision.value(),
							this, surface_type, cycles, allowObstructions);
					}
				}

				// assume reflection at the moment but will depend on the type of surface
				//LOG_INFO("MOLECULE REFLECTED");
				// dont need an internal surface relative
				// just specific a simulation boundary region which has to be a low priority relative
				// of all regions. Therefore a region does not need its own surface type
				// the global region cannot have a membrane surface (can be done with simple json file check)
				// disable collision checks on global region?
				return PassMolecule(end, collision.value(), this, GetDefaultSurfaceType(), cycles,
					allowObstructions);
				//return CheckMoleculePath(collision->intersection, collision->reflection);
			}
			//g_json.clear();
			return MoleculeDestination(end, this);
		}
		else 
		{
			//LOG_ERROR("molecule hit maxiumum interaction cycles");
			//LOG_ERROR(JsonToPrettyString(g_json["path3D"]));
			//g_json.clear();
			return MoleculeDestination(origin, this);
		}
	}

	// dont change old position, create new one.
	Vec3d Grid::DiffuseMolecule(const NormalMolecule& molecule)
	{
		return { molecule.GetPosition() + 
			std::sqrt(2 * diffision_coefficient * GetRegion().GetTimeStep()) *
			Vec3d::GenerateNormal() };
	}

	// will require envionment time to be updated before event is finished or do environment time + time step
	Vec3d Grid::DiffuseMolecule(const RecentMolecule& molecule)
	{
		// will produce nan is molecule time > environment/region time
		// for regions with the same start time and time step delta time should = 0.
		return { molecule.GetPosition() +
			std::sqrt(2 * diffision_coefficient * (region->GetEventTime() - molecule.GetTime())) *
			Vec3d::GenerateNormal() };
	}

	// may need const version
	Region& Grid::GetRegion()
	{
		return *region;
	}

	// may need const version
	std::vector<Subvolume>& Grid::GetSubvolumes()
	{
		return subvolumes;
	}

	// could be private?
	// may need const version
	// will always return a valid subvolume even if index is for a position outside of subvolume
	Subvolume& Grid::GetSubvolume(Vec3i index)
	{
		// if index is below or above index range limit it to within range
		index *= (index > Vec3i(0, 0, 0));
		index.EqualIf((index >= n_subvolumes), n_subvolumes - 1);
		return subvolumes.at(index.x + index.y * n_subvolumes.x + index.z * n_subvolumes.x * n_subvolumes.y);
	}

	// could be private?
	// if index is not valid null will be returned
	Subvolume* Grid::GetSubvolumeIfExists(const Vec3i& index)
	{
		if ((index < Vec3i(0, 0, 0)).Any()) return nullptr;
		if ((index >= n_subvolumes).Any()) return nullptr;
		return &subvolumes.at(index.x + index.y * n_subvolumes.x + index.z * n_subvolumes.x * n_subvolumes.y);
	}

	// could be const if you are only linking local subvolumes and not vice versa
	// would be more efficient to do both at same time. Would then require a check to see if regions are already
	// neighbours. Grid is of same molecule type
	void Grid::LinkGrid(Grid& grid)
	{
		//LOG_INFO("Linking {} to {}", GetMoleculeID(), grid.GetMoleculeID());
		for (auto& s1 : subvolumes)
		{
			for (auto& s2 : grid.subvolumes)
			{
				//LOG_INFO("{}, {}", s1.GetMoleculeID(), s2.GetMoleculeID());
				//LOG_INFO(grid.GetMoleculeID());
				s1.Link(s2);
			}
		}
	}

	// Local grids (excluding itself) only need a one way connection while external need a two way connection
	// every cell needs to be checked for overlap due to different cell sizes.
	void Grid::LinkLocalGrid(Grid& grid)
	{
		// UNECCESSARY? Let region control local grid linking and just call link grid
	}

	const MoleculeID& Grid::GetMoleculeID()
	{
		return id;
	}

	void Grid::AddRelative(NeighbourRelative* relative, SurfaceType type)
	{
		neighbour_relationships.emplace_back(relative, type);
	}

	void Grid::AddRelative(LowPriorityRelative* relative, SurfaceType type)
	{
		low_priority_relationships.emplace_back(relative, type);
	}

	void Grid::AddRelative(HighPriorityRelative* relative, SurfaceType type)
	{
		high_priority_relationships.emplace_back(relative, type);
	}

	// create subvolumes upon class construction
	void Grid::CreateSubvolumes()
	{
		subvolumes.reserve(n_subvolumes.Volume());
		Vec3i i;
		for (i.z = 0; i.z < n_subvolumes.z; i.z++)
		{
			for (i.y = 0; i.y < n_subvolumes.y; i.y++)
			{
				for (i.x = 0; i.x < n_subvolumes.x; i.x++)
				{
					Vec3d subvolume_length = box.GetLength() / n_subvolumes;
					subvolumes.emplace_back(box.GetOrigin() + i * subvolume_length, subvolume_length, this, Environment::GetNumberOfMoleculeTypes());
				}
			}
		}
	}

	// go through each subvolume of the same molecule type
	void Grid::LinkSiblingSubvolumes()
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
	void Grid::LinkSiblingSubvolumes(const Vec3i& i)
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
					// dont link a subvolume to itself
					if (!(j == Vec3i(0)).All())
					{
						//LOG_INFO("Linking sibling subvolumes");
						auto subvolume2 = GetSubvolumeIfExists(i + j);
						//if (subvolume == subvolume2) LOG_INFO("THE SAME");
						if (subvolume2 != nullptr)
						{
							subvolume->LinkSibling(*subvolume2);
						}
					}
				}
			}
		}
	}

	// Inherited Class Functions
	const RegionShape& Grid::GetShape() const
	{
		return region->GetShape();
	}

	SurfaceType Grid::GetDefaultSurfaceType() const
	{
		return surface_type;
	}

	double Grid::GetDiffusionCoeffient() const
	{
		return diffision_coefficient;
	}

	bool Grid::IsRegion() const
	{
		return true;
	}

	const HighPriorityRelative::SurfaceDirection& Grid::GetSurfaceDirection() const
	{
		return surface_direction;
	}

	// the global surface must be absorbing or adsorbing
	// KEEP INTERNAL SURFACE BUT SURFACE PER RELATION IS STILL REQUIRED
	// CAN STILL GET RID OF SURFACE CAN HAVE GET BOUNDARY TYPE AND GET SHAPE
	// internal surface must be reflective, absorbing or adsorbing

	// collision spelt incorrectly
	std::optional<MoleculeDestination> Grid::PassMolecule(const Vec3d& end, 
		const shape::collision::Collision3D& collision, Grid* owner,
		SurfaceType surface_type, int cycles, bool allowObstructions)
	{
		//Absorbing, Adsorbing, Membrane, Reflecting, None
		switch (surface_type)
		{
		case SurfaceType::None:
			return CheckMoleculePath(collision.intersection, end, cycles);
		case SurfaceType::Reflecting:
			if (!allowObstructions) return std::nullopt;
			return owner->CheckMoleculePath(collision.intersection, collision.reflection, cycles);
		case SurfaceType::Absorbing:
			return std::nullopt;
		case SurfaceType::Membrane:
			return CheckMoleculePath(collision.intersection, end, cycles);
		default:
			LOG_CRITICAL("SurfaceType must be None, Reflecting Or Absorbing");
			throw std::exception();
		}
	}
}