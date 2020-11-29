#pragma once
#include "pch.h"
#include "vec3d.h"
#include "relation_box.h"
#include "microscopic_region2.h"

// Moving non owning, low priority surfaces is easy just not owning ones.

namespace accord::microscopic
{
	// a subvolume storing a known type of subvolume
	class TypedSubvolume;

	class NormalMolecule;

	class RecentMolecule;

	class Subvolume2
	{
	public:

		Subvolume2(Vec3d origin, Vec3d length);

		void AddMolecule(const Vec3d& position);

		void AddMolecule(const Vec3d& position, double time);

		// unlikely to need const version
		std::vector<NormalMolecule>& GetNormalMolecules();

		std::vector<RecentMolecule>& GetRecentMolecules();

		// Bimolecular Reactions

		// link a subvolume owned by the same grid
		// Only one sibling needs to know about the relation so two subvolumes are only checked against eachother once
		void LinkSibling(Subvolume2& subvolume);

		// link a subvolume not owned by the same grid
		void Link(Subvolume2& subvolume);

		const std::vector<TypedSubvolume>& GetRelatives() const;

		std::vector<TypedSubvolume>& GetRelatives();

		// may need const version
		TypedSubvolume& GetRelative(MoleculeID id);

		const shape::relation::Box& GetBoundingBox();

	private:
		shape::relation::Box box;
		std::vector<NormalMolecule> normal_molecules;
		std::vector<RecentMolecule> recent_molecules;

		// Sibling subvolumes can go into same relation vector as neighbours but to reduce computation time check
		// siblings first as which siblings are added they must check the other sibling does not already have it as
		// a relation.
		std::vector<TypedSubvolume> relations;
	};
}
