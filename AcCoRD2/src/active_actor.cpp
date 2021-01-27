#include "pch.h"
#include "active_actor.h"
#include "microscopic_region.h"
#include "mesoscopic_region.h"
#include "vec3d.h"

// need to add check so a shape checks all regions it can place molecules in
namespace accord
{
	ActiveActor::ActiveActor(double action_interval, double release_interval, const std::vector<int>& release_molecules,
		int modulation_strength, const std::vector<microscopic::Region*>& microscopic_regions, const std::vector<mesoscopic::Region*>& mesoscopic_regions,
		std::unique_ptr<ActiveActorShape> shape, double start_time, int priority, const ActiveActorID& id)
		: action_interval(action_interval), release_interval(release_interval), release_molecules(release_molecules),
		modulation_strength(modulation_strength), microscopic_regions(microscopic_regions), mesoscopic_regions(mesoscopic_regions), Event(start_time, priority),
		id(id), shape(std::move(shape)), local_time(start_time), last_action_time(start_time), start_time(start_time)
	{
	}

	std::string ActiveActor::LogEvent() const
	{
		return fmt::format("Active Actor. ID:{}, Priority:{}, Time:{}", id, priority, time);
	}

	const ActiveActorID& ActiveActor::GetID() const
	{
		return id;
	}

	ActiveActorShape& ActiveActor::GetShape()
	{
		return *shape;
	}

	void ActiveActor::ReleaseMolecules(int n_releases)
	{
		// TODO: Abstract mesoscopic and microscopic regions by ensuring consistent function names (GetShape and IsMoleculeInsideBorder)
		int max_insert_attempts = 100;
		for (int i = 0; i < n_releases; i++)
		{
			int molecule_id = 0;
			for (int n_molecules : release_molecules)
			{
				for (int n = 0; n < n_molecules; n++)
				{
					int n_insert_attempts = 0;
					bool inserted = false;
					while (n_insert_attempts < max_insert_attempts && !inserted)
					{
						LOG_INFO("Insert attempt: {}", n_insert_attempts);
						Vec3d position = GetShape().GenerateMolecule();
						//LOG_INFO("molecule id = {}, pos = {}", molecule_id, position);
						for (auto& region : microscopic_regions)
						{
							if (region->GetShape().IsMoleculeInsideBorder(position))
							{
								region->AddMolecule(molecule_id, position, local_time);
								inserted = true;
								break;
							}
						}

						for (auto& region : mesoscopic_regions)
						{
							for (auto& subvolume : region->GetSubvolumes())
							{
								if (subvolume.GetBoundingBox().IsWithinOrOnBorder(position))
								{
									subvolume.AddMolecule(molecule_id);
									inserted = true;
									break;
								}
							}
							region->RefreshEventTime();
						}
						n_insert_attempts++;
					}
				}
				molecule_id++;
			}
		}
	}

	// return true if a new symbol needs to be generated
	bool ActiveActor::SetNextReleaseTime(double elapsed_time)
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
	void ActiveActor::NextRealisation()
	{
		SetEventTime(start_time);
		local_time = start_time;
		last_action_time = start_time;
	}
}
