#pragma once
#include "pch.h"
#include "microscopic_subvolume.h"
#include "microscopic_region.h"
#include "vec3i.h"
#include "vec3b.h"

// Questions
// Do molecules get added to the closest subvolume for mesoscopic regions or are they allowed to continue moving
// until they no longer collide with anything? (would allow molecules to skip meso regions and be placed in centre)

// WRONG:
// only regions with a slower timestep should check regions of faster time step. E.g. If(region.timestep < region2.timestep)

namespace accord
{
	class Environment
	{
	public:
		static double GetTime()
		{
			return time;
		}

		static double GetNumberOfMoleculeTypes()
		{
			return num_molecule_types;
		}
	private:
		static double time;
		static int num_molecule_types;
	};
}
// change all structs to classes (easier forward declaration)
// must decide whether to use * of value()
// can i not use has_value()?

namespace accord::microscopic
{
	// can adsorbing surface adsorb multiple molecule types or only 1 per surface?
	class OwningRelation
	{
		virtual void AddRecentMolecule(Vec3d position, double time) = 0;
	};

	// instead of returning the new owner one could pass the current owner
	// for adsorbing surface AddRecentMolecule(position, time, owner)
	// NOOOOOOOOOOOOO
	// have to return new owner as current owner is currently iterating through molecules so needs to 
	// know if molecule was deleted in order to update iterator.

	class Relation // High Priority Relation
	{
	public:
		virtual RegionShape& GetShape() const = 0;

		virtual SurfaceType& GetSurfaceType() const = 0;

		// each surface type can have its own pass molecule function so it can choose what to do with the molecule
		std::optional<Vec3d> PassMolecule(const Vec3d& end, const shape::collision::Collision3D& collison, Grid* owner)
		{
			// if reflected check the path of the reflected molecule in the same region
			return owner->CheckMoleculePath(collison.intersection, collison.reflection, owner);

			// if absorbed then molecule deleted
			return std::nullopt;

			// if passed into another region set new owner and continue path checking in new region
			//owner = this;
			return owner->CheckMoleculePath(collison.intersection, end, owner);

			// if adsorbed set owner to adsorbing surface and set final position to the intersection.
			//owner = this;
			return collison.intersection;

			// is passed through a membrane continue checking position in same region on other side of membrane
			return owner->CheckMoleculePath(collison.intersection, end, owner);
		}
	};

	// make sure to place surfaces as a younger generation or just make sure surface neighbours are checked first
	class Neighbour
	{
	public:
		// function will change the owner so if attempt is successful: owner.checkmoleculepath will be called
		bool AttemptPassMolecule(const Vec3d& intersection, Grid* owner)
		{
			// if membrane
			// IfMoleculeIsOnMembrane()
			// For each grid relation check if molecule is on border (pass to a GridNeighbour)
			// if grid
			// owner = this;
			// if molecule is on border run CheckMoleculePath()
		}
	};

	class Grid
	{
	public:

		// rename n_partitions
		// pass grid pointer to region
		Grid(Vec3d origin, Vec3d length, Vec3i partitions, double diffision_coefficient, Region* region)
			: box(origin, length), partitions(partitions), diffision_coefficient(diffision_coefficient),
			region(region)
		{
			subvolumes.reserve(partitions.Volume());
			CreateSubvolumes();
		}

		void CreateSubvolumes()
		{
			Vec3i i;
			for (i.z = 0; i.z < partitions.z; i.z++)
			{
				for (i.y = 0; i.y < partitions.y; i.y++)
				{
					for (i.x = 0; i.x < partitions.x; i.x++)
					{
						Vec3d subvolume_length = box.GetLength() / partitions;
						subvolumes.emplace_back(box.GetOrigin() + i * subvolume_length, subvolume_length);
					}
				}
			}
		}

		void AddSiblings()
		{
			Vec3i i;
			for (i.z = 0; i.z < partitions.z; i.z++)
			{
				for (i.y = 0; i.y < partitions.y; i.y++)
				{
					for (i.x = 0; i.x < partitions.x; i.x++)
					{
						AddNeighbouringSibling(i);
					}
				}
			}
			
		}

		void AddNeighbouringSibling(const Vec3i& i)
		{
			auto subvolume = GetOptionalSubvolume(i);

			Vec3i j;
			for (j.z = -1; j.z <= 1; j.z++)
			{
				for (j.y = -1; j.y <= 1; j.y++)
				{
					for (j.x = -1; j.x <= 1; j.x++)
					{
						auto subvolume2 = GetOptionalSubvolume(i + j);
						if (subvolume2.has_value())
						{
							subvolume.value().AddSibling(*subvolume2);
						}
					}
				}
			}
		}

		// external neighbours (from a different region)
		void AddNeighbour(Grid& grid) // change to add relatives
		{
			for (auto& subvolume1 : subvolumes)
			{
				auto& b1 = subvolume1.GetBoundingBox();
				for (auto& subvolume2 : grid.GetSubvolumes())
				{
					auto& b2 = subvolume2.GetBoundingBox();
					if (b1.IsOverlapping(b2) || b1.IsFullyNeighbouring(b2))
					{
						subvolume1.AddNeighbour(subvolume2);
						subvolume2.AddNeighbour(subvolume1);
					}
				}
			}
		}

		void AddNormalMolecule(NormalMolecule molecule)
		{
			Vec3i index = Vec3d(partitions) * ((molecule.position - box.GetOrigin()) / box.GetLength());
			GetSubvolume(index).AddNormalMolecule(molecule);
		}

		void AddRecentMolecule(RecentMolecule molecule)
		{
			Vec3d index = Vec3d(partitions) * ((molecule.position - box.GetOrigin()) / box.GetLength());
			GetSubvolume(index).AddRecentMolecule(molecule);
		}

		void DiffuseMolecules()
		{
			for (auto& subvolume : subvolumes)
			{
				// diffuse normal molecules
				auto& molecules = subvolume.GetNormalMolecules();
				for (auto molecule = molecules.begin(); molecule != molecules.end();)
				{
					Grid* owner = this;
					std::optional<Vec3d> new_position = CheckMoleculePath(molecule->position, DiffuseMolecule(*molecule), owner);

					if (new_position.has_value())
					{
						if (owner == this)
						{
							*molecule = new_position.value();
							++molecule;
						}
						else
						{
							owner->AddNormalMolecule(new_position.value());
							molecule = molecules.erase(molecule);
						}
					}
					else
					{
						molecule = molecules.erase(molecule);
					}	
				}

				// recent molecule list can be clear every time
				// must add recent molecules to normal after normal has already been checked
				for (auto& molecule : subvolume.GetRecentMolecules())
				{
					Grid* owner = this;
					std::optional<Vec3d> new_position = CheckMoleculePath(molecule.position, DiffuseMolecule(molecule), owner);
					
					if (new_position.has_value())
					{
						owner->AddNormalMolecule(new_position.value());
					}
				}
			}
		}
	
		// passing owner is not necessary, just store owner in the return as the owner will always be the one
		// calling the CheckMoleculePath() function
		// Relation.PassMolecule() still needs to know the owner
		std::optional<Vec3d> CheckMoleculePath(const Vec3d& origin, const Vec3d& end, Grid* owner)
		{

			// closest relation could also be a surface
			std::optional<Relation> closest_relation;

			// consider renaming Collision3D to Data3D
			shape::collision::Collision3D closest_collision;
			double shortest_time = 2; // collision time must be between 0 and 1 therefore any valid collision time
			// will be less than 2.
			for (auto& relation : high_priority_relations)
			{
				auto collision = relation.GetShape().CalculateExternalCollisionData(origin, end);
				if (collision.has_value() && collision->time < shortest_time)
				{
					closest_relation = relation;
					closest_collision = collision.value();
				}
			}

			if (closest_relation.has_value())
			{
				return closest_relation->PassMolecule(end, closest_collision, owner);
			}

			auto collision = GetRegion().GetRegionShape().CalculateExternalCollisionData(origin, end);
			if (collision.has_value())
			{
				for (auto& relation : low_priority_relations)
				{
					if (relation.GetRegion().GetRegionShape().IsMoleculeInsideBorder(collision->intersection))
					{
						owner = &relation;
						// assumes you dont have mulitple valid low priority neighbours overlapping

						// will have to change as mesoregions dont check molecule path? Or do they?
						return relation.CheckMoleculePath(collision->intersection, end, owner);
					}
				}

				for (auto& neighbour : neighbours)
				{
					// will no longer work due to meso regions
					// meso neighbour no longer need to check molecule path
					if (neighbour.AttemptPassMolecule(collision->intersection, owner))
					{
						return owner->CheckMoleculePath(collision->intersection, end, owner);
					}

					// meso solution
					/* if(neighbour.IsMoleculeOnNeighbour())
					*  then [position] = PassMolecule(intersection, end, owner)
					* grid runs CheckMoleculePath()
					* membrane finds the correct grid and it called checkpath; // will throw error if no grid found
					* in relation setup surfaces must not have any unnamed neighbours
					* meso region just returns [position, owner = meso]
					*/
				}
			}
		}

		// dont change old position, create new one.
		Vec3d DiffuseMolecule(const NormalMolecule& molecule)
		{
			return { molecule.position + std::sqrt(2 * diffision_coefficient * region->GetTimeStep()) *
				Vec3d(Random::GenerateNormal(), Random::GenerateNormal(), Random::GenerateNormal()) };
		}

		// will require envionment time to be updated before event is finished or do environment time + time step
		Vec3d DiffuseMolecule(const RecentMolecule& molecule)
		{
			return { molecule.position +
				std::sqrt(2 * diffision_coefficient * (Environment::GetTime() - molecule.time)) *
				Vec3d(Random::GenerateNormal(), Random::GenerateNormal(), Random::GenerateNormal())};
		}

		Region& GetRegion()
		{
			return *region;
		}

		std::vector<Subvolume>& GetSubvolumes() // could have another const version
		{
			return subvolumes;
		}

	private:
		// will always return a valid subvolume even if index is for a position outside of subvolume
		Subvolume& GetSubvolume(Vec3i index)
		{
			// if any of the indicies along any axis are less than 0 (could be due to floating point error)
			// then set the index of that axis to 0, else leave as is.
			index *= (index < Vec3i(0, 0, 0));
			// if index along any axis is equal to or greater than number of partitions set it to partitions - 1
			index.EqualIf((index >= partitions), partitions - 1);

			return subvolumes.at(index.x + index.y * partitions.x + index.z * partitions.x * partitions.y);
		}

		// if index is not valid null will be returned
		std::optional<Subvolume&> GetOptionalSubvolume(const Vec3i& index)
		{
			if ((index < Vec3i(0, 0, 0)).Any()) return std::nullopt;
			if ((index >= partitions).Any()) return std::nullopt;
			return subvolumes.at(index.x + index.y * partitions.x + index.z * partitions.x * partitions.y);
		}

		// all relation types can be surfaces
		// RelationTypeRequirements: GetSurfaceType(), CalculatePositive/ExternalReflection() 
		// CalculateNegative/InternalReflection()

		// need to specify direction of low and high relations
		// neighbours regions/surfaces just need to check OnBoundary / On Surface

		// neighbours and high low priority relations INCLUDE MESOREGIONS!!
		std::vector<Neighbour> neighbours;
		std::vector<Grid> low_priority_relations; // CHANGE to LowPriorityRelation
		std::vector<Relation> high_priority_relations; // CHANGE to HighPriorityRelation
		// rename relation to relatives?
		// high priority relations can be non-owning or owning (check internal/external collision)
		// low priority relations have to be grids (check is molecule inside border) (NOT SURFACES)
		// neighbours relations have to be grids or membranes

		// neighbour.IsMoleculeOnBorder()
		// if so then pass
		// as membranes are neighbours will have to do
		// neighbour.PassMolecule()
		// 1. grid relations will check IfMoleculeIsOnBorder() then run CheckMoleculePath()
		// 2. membrane relations will check IfMoleculeIsOnBorder() then for each of its grid relations check 
		// IfMoleculeIsOnBorder() then run CheckMoleculePath()

		double time_step; // move to region
		double local_simulation_time; // move to region

		double diffision_coefficient;
		Vec3i partitions;
		std::vector<Subvolume> subvolumes;
		shape::relation::Box box; // the shape of a region can be a (relation and collision) box but the grid must always be a (relation) box
		Region* region; // regions which owns this grid
		
	};
}