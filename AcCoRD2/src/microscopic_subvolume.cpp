#include "pch.h"
#include "microscopic_subvolume.h"
#include "microscopic_grid.h"

namespace accord::microscopic
{
	Subvolume::Subvolume(const Vec3d& origin, const Vec3d& length, Grid* grid, int n_molecule_types, int subvolume_id)
		: box(origin, length), grid(grid), is_reacting(false), subvolume_id(subvolume_id)
	{
		//LOG_INFO("Subvolume id = {}, molecule id = {}, origin = {}, length = {}", subvolume_id, grid->GetMoleculeID(), origin, length);
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
			//LOG_INFO("SiblingA id = {}, molecule id = {}, box = {}", subvolume_id, GetMoleculeID(), box);
			//LOG_INFO("SiblingB id = {}, molecule id = {}, box = {}", subvolume.subvolume_id, subvolume.GetMoleculeID(), subvolume.box);
		}
	}

	void Subvolume::LinkCousin(Subvolume& subvolume)
	{
		GetRelation(subvolume.GetMoleculeID()).Add(subvolume);
		//LOG_INFO("CousinA id = {}, molecule id = {}", subvolume_id, GetMoleculeID());
		//LOG_INFO("CousinB id = {}, molecule id = {}\n", subvolume.subvolume_id, subvolume.GetMoleculeID());
	}

	// link a subvolume not owned by the same grid
	void Subvolume::Link(Subvolume& subvolume)
	{
		LOG_INFO("SubvolumeA id = {}, molecule id = {}, box = {}", subvolume_id, GetMoleculeID(), box);
		LOG_INFO("SubvolumeB id = {}, molecule id = {}, box = {} \n", subvolume.subvolume_id, subvolume.GetMoleculeID(), subvolume.box);
		if (box.IsOverlapping(subvolume.box) || box.IsPartiallyNeighbouring(subvolume.box))
		{
			LOG_INFO("{} {}", box.IsOverlapping(subvolume.box), box.IsPartiallyNeighbouring(subvolume.box));
			//if (&subvolume == this) LOG_ERROR("attempt to add same subvolume");
			GetRelation(subvolume.GetMoleculeID()).Add(subvolume);
		}
		
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

	bool& Subvolume::GetIsReacting()
	{
		return is_reacting;
	}

	int Subvolume::GetSubvolumeID()
	{
		return subvolume_id;
	}

	MoleculeID Subvolume::GetMoleculeID()
	{
		return GetGrid().GetMoleculeID();
	}
}