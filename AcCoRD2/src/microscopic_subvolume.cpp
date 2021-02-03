#include "pch.h"
#include "microscopic_subvolume.h"
#include "microscopic_grid.h"

namespace accord::microscopic
{
	Subvolume::Subvolume(const Vec3d& origin, const Vec3d& length, Grid* grid, int n_molecule_types)
		: box(origin, length), grid(grid)
	{
		//LOG_INFO("grid origin = {}, length = {}", origin, length);
		relations.reserve(n_molecule_types);
		for (int i = 0; i < n_molecule_types; i++)
		{
			relations.emplace_back();
		}
	}

	void Subvolume::AddMolecule(const Vec3d& position)
	{
		normal_molecules.emplace_back(position);
	}

	void Subvolume::AddMolecule(const Vec3d& position, double time)
	{
		recent_molecules.emplace_back(position, time);
	}

	// unlikely to need const version
	std::vector<NormalMolecule>& Subvolume::GetNormalMolecules()
	{
		return normal_molecules;
	}

	std::vector<NormalMolecule>& Subvolume::GetNormalDiffusionMolecules()
	{
		return normal_diffusion_molecules;
	}

	std::vector<RecentMolecule>& Subvolume::GetRecentMolecules()
	{
		return recent_molecules;
	}

	// link a subvolume owned by the same grid
	// Only one sibling needs to know about the relation so two subvolumes are only checked against eachother once
	void Subvolume::LinkSibling(Subvolume& subvolume)
	{
		//if (&subvolume == this) LOG_ERROR("attempt to add same subvolume");
		auto& relatives = subvolume.GetRelation(GetMoleculeID()).GetSubvolumes();
		// if subvolume does not contain this subvolume then add subvolume to this subvolume
		if (std::find(relatives.begin(), relatives.end(), this) == relatives.end())
		{
			relations.at(GetMoleculeID()).Add(subvolume);
		}
	}

	// link a subvolume not owned by the same grid
	void Subvolume::Link(Subvolume& subvolume)
	{
		//if (&subvolume == this) LOG_ERROR("attempt to add same subvolume");
		GetRelation(subvolume.GetMoleculeID()).Add(subvolume);
	}

	const std::vector<TypedSubvolume>& Subvolume::GetRelations() const
	{
		return relations;
	}

	std::vector<TypedSubvolume>& Subvolume::GetRelations()
	{
		return relations;
	}

	// may need const version
	TypedSubvolume& Subvolume::GetRelation(const MoleculeID& id)
	{
		return relations.at(id);
	}

	const shape::relation::Box& Subvolume::GetBoundingBox()
	{
		return box;
	}

	Grid& Subvolume::GetGrid()
	{
		return *grid;
	}

	std::vector<bool>& Subvolume::GetHasReacted()
	{
		return has_reacted;
	}

	std::vector<NormalMolecule>& Subvolume::GetNonReactedNormalMolecules()
	{
		return non_reacted_normal_molecules;
	}

	MoleculeID Subvolume::GetMoleculeID()
	{
		return GetGrid().GetMoleculeID();
	}
}