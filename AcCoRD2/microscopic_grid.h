#pragma once
#include "pch.h"
#include "microscopic_subvolume.h"
#include "microscopic_region.h"

namespace accord
{
	class Environment
	{
	public:
		static double GetTime()
		{
			return time;
		}
	private:
		static double time;
	};
}

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

	class Relation
	{
	public:
		RegionShape& GetShape();

		SurfaceType& GetSurfaceType();

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

	class Neighbour
	{
		std::optional<Vec3d> PassMolecule(const Vec3d& intersection, const Vec3d& end, Grid* owner)
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
		void AddNormalMolecule(NormalMolecule molecule)
		{
			Vec3d index = (molecule.position - box.GetOrigin()) / box.GetLength();
			GetSubvolume(index).AddNormalMolecule(molecule);
		}

		void AddRecentMolecule(RecentMolecule molecule)
		{
			Vec3d index = (molecule.position - box.GetOrigin()) / box.GetLength();
			GetSubvolume(index).AddRecentMolecule(molecule);
		}

		void DiffuseMolecules()
		{
			for (auto& subvolume : subvolumes)
			{
				for (auto& molecule : subvolume.GetNormalMolecules())
				{

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
						relation.CheckMoleculePath(collision->intersection, end, owner);
					}
				}
			}

			for (auto& neighbour : neighbours)
			{

			}
		}

		// dont change old position, create new one.
		void DiffuseNormalMolecule(NormalMolecule& molecule)
		{
			double magnitude = std::sqrt(2 * diffision_coefficient * time_step);
			molecule.position.x += Random::GenerateNormal() * magnitude;
			molecule.position.y += Random::GenerateNormal() * magnitude;
			molecule.position.z += Random::GenerateNormal() * magnitude;
		}

		void DiffuseRecentMolecule(RecentMolecule& molecule)
		{
			double magnitude = std::sqrt(2 * diffision_coefficient * (Environment::GetTime() - molecule.time));
			molecule.position.x += Random::GenerateNormal() * magnitude;
			molecule.position.y += Random::GenerateNormal() * magnitude;
			molecule.position.z += Random::GenerateNormal() * magnitude;
		}

		Region& GetRegion()
		{
			return *region;
		}

	private:
		Subvolume& GetSubvolume(Vec3d index)
		{
			return subvolumes.at(index.x + index.y * partitions.x + index.z * partitions.x * partitions.y);
		}

		// all relation types can be surfaces
		// RelationTypeRequirements: GetSurfaceType(), CalculatePositive/ExternalReflection() 
		// CalculateNegative/InternalReflection()

		// need to specify direction of low and high relations
		// neighbours regions/surfaces just need to check OnBoundary / On Surface
		std::vector<Neighbour> neighbours;
		std::vector<Grid> low_priority_relations; // CHANGE to GRID
		std::vector<Relation> high_priority_relations; // rename relation to relatives?
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

		double time_step;
		double simulation_time;

		double diffision_coefficient;
		Vec3d partitions;
		std::vector<Subvolume> subvolumes;
		shape::relation::Box box; // the shape of a region can be a (relation and collision) box 
		Region* region; // regions which owns this grid
		// but the grid must always be a (relation) box
	};
}