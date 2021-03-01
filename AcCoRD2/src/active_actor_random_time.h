#pragma once
#include "active_actor.h"

namespace accord
{
	class ActiveActorRandomTime : public ActiveActor
	{
	public:
		ActiveActorRandomTime(double action_interval, double release_interval,
			const std::vector<int>& release_molecules, int modulation_strength, const std::vector<microscopic::Region*>& micro_regions,
			const std::vector<mesoscopic::Region*>& meso_regions, std::unique_ptr<ActiveActorShape> shape,
			double start_time, int priority, const ActiveActorID& id);

		void Run();

		void NextRealisation();
	private:
		double release_coefficient;

		double GenerateDeltaTime();

		double CalculateReleaseCoefficient(double modulation_strength);
	};
};
