#pragma once
#include "pch.h"
#include "vec3d.h"
#include "relation_box.h"

namespace accord::microscopic
{
	class Subvolume;

	class TypedSubvolumes
	{
	public:
		void Add(Subvolume* subvolume)
		{
			subvolumes.emplace_back(subvolume);
		}

		std::vector<Subvolume*> subvolumes;
	};

	class NormalMolecule
	{
	public:
		Vec3d position;

		NormalMolecule(Vec3d position)
			: position(position)
		{

		}
	};

	class RecentMolecule
	{
	public:
		Vec3d position;
		double time;

		RecentMolecule(Vec3d position, double time)
			: position(position), time(time)
		{

		}
	};

	class Subvolume
	{
	public:

		Subvolume(Vec3d origin, Vec3d length)
			: box(origin, length)
		{

		}

		void AddNormalMolecule(NormalMolecule normal_molecule)
		{
			
		}

		void AddRecentMolecule(RecentMolecule normal_molecule)
		{
			
		}

		std::vector<NormalMolecule>& GetNormalMolecules()
		{
			return normal_molecules;
		}

		std::vector<RecentMolecule>& GetRecentMolecules()
		{
			return recent_molecules;
		}

		// Bimolecular Reactions

		// Add a subvolume of the same type which is owned by the same microscopic region
		// Only one sibling needs to know about the relation so two subvolumes are only checked against eachother once
		void AddSibling(Subvolume subvolume)
		{
			auto relatives = subvolume.GetRelatives();
			// if subvolume does not contain this subvolume then add subvolume to this subvolume
			if (std::find(relatives.begin(), relatives.end(), *this) == relatives.end())
			{
				relations.at(molecule_id).Add(&subvolume);
			}
		}

		const std::vector<TypedSubvolumes>& GetRelatives() const
		{
			return relations;
		}

		// Add a subvolume of a different type which is owned by the same microscopic region, or add a subvolume 
		// owned by a different microscopic region (same or different type).
		// To save neighbour checks, only the subvolumes with the lower molecule id between neighbours for
		// subvolumes of different types owned by the same microscopic region, need to know about the relationship.
		// Must ensure bi-molecular reaction reactants are ordered lower molecule type id first.
		void AddNeighbour(Subvolume subvolume)
		{
			relations.at(molecule_id).Add(&subvolume);
		}

		const shape::relation::Box& GetBoundingBox()
		{
			return box;
		}
	private:

		shape::relation::Box box;
		int molecule_id; // consider getting as pointer from grid. Could add private function GetMoleculeID()

		std::vector<NormalMolecule> normal_molecules;
		std::vector<RecentMolecule> recent_molecules;

		// Bimolecular Reactions

		// Sibling subvolumes can go into same relation vector as neighbours but to reduce computation time check
		// siblings first as which siblings are added they must check the other sibling does not already have it as
		// a relation.
		std::vector<TypedSubvolumes> relations;
	};
}
