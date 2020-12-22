#pragma once
#include "pch.h"
#include "vec3d.h"
#include "relation_box.h"
#include "microscopic_normal_molecule.h"
#include "microscopic_recent_molecule.h"
#include "microscopic_typed_subvolume.h"

// Moving non owning, low priority surfaces is easy just not owning ones.

namespace accord::microscopic
{
	class Grid2;

	class Subvolume2
	{
	public:

		Subvolume2(Vec3d origin, Vec3d length, Grid2* grid);

		void AddMolecule(const Vec3d& position);

		void AddMolecule(const Vec3d& position, double time);

		// unlikely to need const version
		std::vector<NormalMolecule>& GetNormalMolecules();

		std::vector<RecentMolecule>& GetRecentMolecules();

		// link a subvolume owned by the same grid (thus same molecule id)
		// Only one sibling needs to know about the relation so two subvolumes are only checked against eachother once
		void LinkSibling(Subvolume2& subvolume);

		// link a subvolume not owned by the same grid (thus molecule id needs to be provided)
		void Link(Subvolume2& subvolume);

		const std::vector<TypedSubvolume>& GetRelations() const;

		std::vector<TypedSubvolume>& GetRelations();

		// may need const version
		TypedSubvolume& GetRelation(MoleculeID id);

		const shape::relation::Box& GetBoundingBox();

		MoleculeID GetMoleculeID();

		Grid2& GetGrid();

		void ResetReactionList(double time);

		std::vector<bool> GetHasReactedList();

	private:
		Grid2* grid; // the grid which owns this subvolume
		shape::relation::Box box;
		std::vector<NormalMolecule> normal_molecules;
		std::vector<RecentMolecule> recent_molecules;

		// Sibling subvolumes can go into same relation vector as neighbours but to reduce computation time check
		// siblings first as which siblings are added they must check the other sibling does not already have it as
		// a relation.
		std::vector<TypedSubvolume> relations;

		// if the last second order reaction time is less than the current time then refresh second order reaction has reacted list.
		double last_second_order_reaction_time;
		// only for normal molecules
		std::vector<bool> has_reacted;
	};
}
