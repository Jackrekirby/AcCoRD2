#include "pch.h"
#include "microscopic_subvolume2.h"
#include "microscopic_grid2.h"

namespace accord::microscopic
{
	Subvolume2::Subvolume2(Vec3d origin, Vec3d length, Grid2* grid, int n_molecule_types)
		: box(origin, length), grid(grid)
	{
		//LOG_INFO("grid id = {}", grid->GetMoleculeID());
		relations.reserve(n_molecule_types);
		for (int i = 0; i < n_molecule_types; i++)
		{
			relations.emplace_back();
		}
	}

	void Subvolume2::AddMolecule(const Vec3d& position)
	{
		normal_molecules.emplace_back(position);
	}

	void Subvolume2::AddMolecule(const Vec3d& position, double time)
	{
		recent_molecules.emplace_back(position, time);
	}

	// unlikely to need const version
	std::vector<NormalMolecule>& Subvolume2::GetNormalMolecules()
	{
		return normal_molecules;
	}

	std::vector<RecentMolecule>& Subvolume2::GetRecentMolecules()
	{
		return recent_molecules;
	}

	// link a subvolume owned by the same grid
	// Only one sibling needs to know about the relation so two subvolumes are only checked against eachother once
	void Subvolume2::LinkSibling(Subvolume2& subvolume)
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
	void Subvolume2::Link(Subvolume2& subvolume)
	{
		//if (&subvolume == this) LOG_ERROR("attempt to add same subvolume");
		GetRelation(subvolume.GetMoleculeID()).Add(subvolume);
	}

	const std::vector<TypedSubvolume>& Subvolume2::GetRelations() const
	{
		return relations;
	}

	std::vector<TypedSubvolume>& Subvolume2::GetRelations()
	{
		return relations;
	}

	// may need const version
	TypedSubvolume& Subvolume2::GetRelation(MoleculeID id)
	{
		return relations.at(id);
	}

	const shape::relation::Box& Subvolume2::GetBoundingBox()
	{
		return box;
	}

	Grid2& Subvolume2::GetGrid()
	{
		return *grid;
	}

	MoleculeID Subvolume2::GetMoleculeID()
	{
		return GetGrid().GetMoleculeID();
	}
}