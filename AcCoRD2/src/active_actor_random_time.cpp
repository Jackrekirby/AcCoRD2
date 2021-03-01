#include "pch.h"
#include "active_actor_random_time.h"

namespace accord
{
	ActiveActorRandomTime::ActiveActorRandomTime(double action_interval, double release_interval,
		const std::vector<int>& release_molecules, int modulation_strength, const std::vector<microscopic::Region*>& micro_regions,
		const std::vector<mesoscopic::Region*>&  meso_regions, std::unique_ptr<ActiveActorShape> shape,
		double start_time, int priority, const ActiveActorID& id)
		: ActiveActor(action_interval, release_interval, release_molecules, modulation_strength, micro_regions, meso_regions, std::move(shape),
			start_time, priority, id), release_coefficient(CalculateReleaseCoefficient(modulation_strength))
	{
		//LOG_INFO("release coefficient = {}", release_coefficient);
		double first_release_time = start_time + GenerateDeltaTime();
		SetTimeNoUpdate(first_release_time);
		local_time = first_release_time;
		last_action_time = first_release_time;
	}

	void ActiveActorRandomTime::Run()
	{
		if (!SetNextReleaseTime(GenerateDeltaTime()))
		{
			ReleaseMolecules(1);
		}
	}

	void ActiveActorRandomTime::NextRealisation()
	{
		double first_release_time = start_time + GenerateDeltaTime();
		SetEventTime(first_release_time);
		local_time = first_release_time;
		last_action_time = first_release_time;
	}

	double ActiveActorRandomTime::GenerateDeltaTime()
	{
		return (release_coefficient * log(Random::GenerateRealUniform()));
	}

	double ActiveActorRandomTime::CalculateReleaseCoefficient(double modulation_strength)
	{
		return (-1 / (modulation_strength * GetShape().CalculateVolume()));
	}
};
