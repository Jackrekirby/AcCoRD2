#include "pch.h"
#include "mesoscopic_region.h"
#include "vec3d.h"
#include "vec3i.h"
#include "vec3b.h"

namespace accord::mesoscopic
{
	Region::Region(const Vec3d& origin, double subvolume_length, const Vec3i& n_subvolumes, 
		const std::vector<double>& diffusion_coefficients, int priority, const MesoscopicRegionID& id)
		: box(origin, subvolume_length * Vec3d(n_subvolumes)), Event(0, priority), id(id),
			n_subvolumes(n_subvolumes), subvolume_length(subvolume_length)
	{
		LOG_INFO("n subs = {}", n_subvolumes);
		CreateSubvolumes(n_subvolumes, diffusion_coefficients, subvolume_length);
	}

	void Region::AddMolecule(const MoleculeID& id, const Vec3d& position)
	{
		//LOG_INFO("molecule id = {}", id);
		Vec3i index = Vec3d(n_subvolumes) * ((position - box.GetOrigin()) / box.GetLength());
		GetSubvolume(index).AddMolecule(id);
		RefreshEventTime();
	}

	void Region::AddSubvolumesToQueue()
	{
		// now subvolumes are confirmed delete subvolumes marked for deletion (because other regions have replaced the subvolumes)
		LOG_INFO("num_subvolume = {}", subvolumes.size());
		std::vector<Subvolume> new_subvolumes;
		for (auto& subvolume : subvolumes)
		{
			if (!subvolume.IsMarkedForDeletion())
			{
				new_subvolumes.emplace_back(subvolume);
			}
			else
			{
				LOG_INFO("is marked for deletion");
			}
		}
		subvolumes = new_subvolumes;
		LOG_INFO("num_subvolume = {}", subvolumes.size());
		subvolume_queue.Reserve(subvolumes.size());
		for (auto& subvolume : subvolumes)
		{
			subvolume_queue.Add(&subvolume);
			subvolume.UpdateReactionTime();
			//LOG_INFO("subvolume propensity = {}, time = {}", subvolume.GetPropensity(), subvolume.GetTime());
			
		}

		SetEventTime(subvolume_queue.Front().GetTime());
	}

	void Region::LinkSiblingSubvolumes()
	{
		Vec3i i;
		for (i.z = 0; i.z < n_subvolumes.z; i.z++)
		{
			for (i.y = 0; i.y < n_subvolumes.y; i.y++)
			{
				for (i.x = 0; i.x < n_subvolumes.x; i.x++)
				{
					LOG_INFO("linking at index = {}", i);
					
					if (!GetSubvolume(i).IsMarkedForDeletion())
					{
						LinkSiblingSubvolumes(i);
					}
				}
			}
		}
	}

	// for a given cell check the 26 cells surrounding it and link them if they are not already linked
	void Region::LinkSiblingSubvolumes(const Vec3i& i)
	{
		// should always be passing a valid subvolume;
		auto subvolume = GetSubvolumeIfExists(i);
		if (subvolume == nullptr)
		{
			LOG_CRITICAL("Index of subvolume is out of range. Index = [{}]", i);
			throw std::exception();
		}

		std::array<Vec3i, 6> offsets = { Vec3i(1, 0, 0), {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1} };
		for (auto& offset : offsets)
		{
			//LOG_INFO("Linking sibling subvolumes");
			auto subvolume2 = GetSubvolumeIfExists(i + offset);
			if (subvolume2 != nullptr && !subvolume2->IsMarkedForDeletion())
			{
				LOG_INFO("nieghbour ids = {}, {}", subvolume->GetID(), subvolume2->GetID());
				subvolume->AddNeighbour(*subvolume2);
			}
		}
	}

	// will always return a valid subvolume even if index is for a position outside of subvolume
	Subvolume& Region::GetSubvolume(Vec3i index)
	{
		// if index is below or above index range limit it to within range
		index *= (index > Vec3i(0, 0, 0));
		index.EqualIf((index >= n_subvolumes), n_subvolumes - 1);
		return subvolumes.at(index.x + index.y * n_subvolumes.x + index.z * n_subvolumes.x * n_subvolumes.y);
	}

	// could be private?
	// if index is not valid null will be returned
	Subvolume* Region::GetSubvolumeIfExists(const Vec3i& index)
	{
		if ((index < Vec3i(0, 0, 0)).Any()) return nullptr;
		if ((index >= n_subvolumes).Any()) return nullptr;
		return &subvolumes.at(index.x + index.y * n_subvolumes.x + index.z * n_subvolumes.x * n_subvolumes.y);
	}

	void Region::CreateSubvolumes(const Vec3i& n_subvolumes, 
		std::vector<double> diffusion_coefficients, double subvolume_length)
	{
		subvolumes.reserve(n_subvolumes.Volume());
		Vec3i i;
		int j = 0;
		for (i.z = 0; i.z < n_subvolumes.z; i.z++)
		{
			for (i.y = 0; i.y < n_subvolumes.y; i.y++)
			{
				for (i.x = 0; i.x < n_subvolumes.x; i.x++)
				{
					subvolumes.emplace_back(box.GetOrigin() + Vec3d(i) * subvolume_length, 
						subvolume_length, diffusion_coefficients, j);
					j++;
				}
			}
		}
	}

	std::vector<Subvolume>& Region::GetSubvolumes()
	{
		return subvolumes;
	}

	void Region::AddZerothOrderReaction(const MoleculeIDs& products, double reaction_rate)
	{
		for (auto& subvolume : subvolumes)
		{
			subvolume.AddZerothOrderReaction(products, reaction_rate);
		}
	}

	void Region::AddFirstOrderReaction(const MoleculeID& reactant, const MoleculeIDs& products, double reaction_rate)
	{
		for (auto& subvolume : subvolumes)
		{
			subvolume.AddFirstOrderReaction(reactant, products, reaction_rate);
		}
	}

	void Region::AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b, const MoleculeIDs& products, double reaction_rate)
	{
		for (auto& subvolume : subvolumes)
		{
			subvolume.AddSecondOrderReaction(reactant_a, reactant_b, products, reaction_rate);
		}
	}

	void Region::RefreshEventTime()
	{
		//LOG_INFO("time = {}", subvolume_queue.Front().GetTime());
		SetEventTime(subvolume_queue.Front().GetTime());
	}

	// will delete subvolumes from the region in preparation for another mesoscopic or microscopic region to be placed inside
	void Region::AddChild()
	{
		// for both meso and microscopic regions
		// check for intersection with each subvolume and delete those which intersect
		// for those which neighbour add as neighbour (just send across to the add neighbour function
	}

	void Region::AddNeighbour(Region& other)
	{
		// for those which neighbour add as neighbour
		// each subvolume is checked against every other subvolume.
		// Inefficient but as only done once not a high priority performace improvement unless a region contains 1000's of subvolumes
		if (box.IsPartiallyNeighbouring(other.box))
		{
			for (auto& s1 : subvolumes)
			{
				auto& b1 = s1.GetBoundingBox();
				for (auto& s2 : other.subvolumes)
				{
					auto& b2 = s2.GetBoundingBox();
					if (b1.IsPartiallyNeighbouring(b2))
					{
						s1.AddNeighbour(s2, &other);
						LOG_INFO("subvolumes {} and {} are neighbours", s1.GetID(), s2.GetID());
					}
				}
			}
		}
		else
		{
			LOG_WARN("Attempted to add mesoscopic region as neighbour but the regions do not neighbour");
		}
	}

	// returns the required dimensions of the replacement region to ensure correct neighbouring (avoid floating point error)
	shape::basic::Box Region::RemoveInterior(const Vec3i& origin_subvolume, const Vec3i& n_subvolumes)
	{
		
		Vec3i i = origin_subvolume;
		Vec3i end_subvolume = origin_subvolume + n_subvolumes;
		LOG_INFO("HERE {} {} {}", origin_subvolume, n_subvolumes, end_subvolume);
		for (i.x = origin_subvolume.x; i.x < end_subvolume.x; i.x++)
		{
			for (i.y = origin_subvolume.y; i.y < end_subvolume.y; i.y++)
			{
				for (i.z = origin_subvolume.z; i.z < end_subvolume.z; i.z++)
				{
					LOG_INFO("removing i = {}, {}", i, i.x + i.y * this->n_subvolumes.x + i.z * this->n_subvolumes.x * this->n_subvolumes.y);
					Subvolume* s = GetSubvolumeIfExists(i);
					if (s != nullptr)
					{
						s->MarkForDeletion();
					}
					else
					{
						LOG_INFO("subvolume cannot be deleted as it does not exist");
					}
					
				}
			}
		}
		return { box.GetOrigin() + Vec3d(origin_subvolume) * subvolume_length, subvolume_length * Vec3d(n_subvolumes) };
	}

	std::string Region::LogEvent() const
	{
		return fmt::format("Microscopic Region. ID:{}, Priority:{}, Time:{}", id, priority, time);
	}

	void Region::Run()
	{
		subvolume_queue.Front().Run();
		SetEventTime(subvolume_queue.Front().GetTime());
		//LOG_INFO("event time = {}", GetEventTime());
	}

	void Region::Print()
	{
		for (auto& subvolume : subvolumes)
		{
			LOG_INFO("id = {}, time = {}", subvolume.GetID(), subvolume.GetTime());
		}
	}

	const shape::relation::Box& Region::GetBoundingBox() const
	{
		return box;
	}

	void Region::NextRealisation()
	{
		for (auto& subvolume : subvolumes)
		{
			subvolume.NextRealisation();
		}
		RefreshEventTime();
	}

	void Region::ToJson(Json& j) const
	{
		j["type"] = "gridBox";
		j["origin"] = box.GetOrigin();
		j["length"] = box.GetLength();
		j["end"] = box.GetEnd();
		j["nPartitions"] = n_subvolumes;
	}

	void to_json(Json& j, const Region& region)
	{
		region.ToJson(j);
	}
}