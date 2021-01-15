#include "pch.h"
#include "active_actor2.h"
#include "microscopic_region2.h"
#include "mesoscopic_region.h"
#include "vec3d.h"

// need to add check so a shape checks all regions it can place molecules in
namespace accord
{
	ActiveActor2::ActiveActor2(double action_interval, double release_interval, const MoleculeIDs& release_molecules,
		int modulation_strength, const std::vector<microscopic::Region*>& microscopic_regions, const std::vector<mesoscopic::Region*>& mesoscopic_regions,
		std::unique_ptr<ActiveActorShape> shape, double start_time, int priority, const ActiveActorID& id)
		: action_interval(action_interval), release_interval(release_interval), release_molecules(release_molecules),
		modulation_strength(modulation_strength), microscopic_regions(microscopic_regions), mesoscopic_regions(mesoscopic_regions), Event5(start_time, priority),
		id(id), shape(std::move(shape)), local_time(start_time), last_action_time(start_time), start_time(start_time)
	{
	}

	std::string ActiveActor2::LogEvent() const
	{
		return fmt::format("Active Actor. ID:{}, Priority:{}, Time:{}", id, priority, time);
	}

	const ActiveActorID& ActiveActor2::GetID() const
	{
		return id;
	}

	ActiveActorShape& ActiveActor2::GetShape()
	{
		return *shape;
	}

	void ActiveActor2::ReleaseMolecules(int n_releases)
	{
		// TODO: Abstract mesoscopic and microscopic regions by ensuring consistent function names (GetShape and IsMoleculeInsideBorder)
		for (int i = 0; i < n_releases; i++)
		{
			for (MoleculeID molecule : release_molecules)
			{
				LOG_INFO("molecule id = {}", molecule);
				Vec3d position = GetShape().GenerateMolecule();
				for (auto& region : microscopic_regions)
				{
					if (region->GetShape().IsMoleculeInsideBorder(position))
					{
						region->AddMolecule(molecule, position, local_time);
						break;
					}
				}

				for (auto& region : mesoscopic_regions)
				{
					if (region->GetBoundingBox().IsWithinOrOnBorder(position))
					{
						region->AddMolecule(molecule, position);
						break;
					}
				}
			}
		}
	}

	// return true if a new symbol needs to be generated
	bool ActiveActor2::SetNextReleaseTime(double elapsed_time)
	{
		LOG_INFO("local time = {}, last_action_time = {}, elapsed_time = {}, delta = {}", local_time, last_action_time, elapsed_time, local_time - last_action_time);
		local_time += elapsed_time; // or random time
		if (local_time - last_action_time < release_interval)
		{
			//LOG_INFO("time still within release time {}", local_time);
			// time still within release interval
			SetEventTime(local_time);
			return false;
		}
		else // local_time - last_action_time >= release_interval
		{
			// release interval passed so must wait until next action interval
			//LOG_INFO("wait until next action interval", local_time);
			last_action_time += action_interval;
			local_time = last_action_time;
			SetEventTime(local_time);
			return true;
		}
	}
	void ActiveActor2::NextRealisation()
	{
		SetEventTime(start_time);
		local_time = start_time;
		last_action_time = start_time;
	}
}
