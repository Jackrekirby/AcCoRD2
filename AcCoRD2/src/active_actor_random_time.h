#pragma once
#include "active_actor2.h"

namespace accord
{
	class ActiveActorRandomTime : public ActiveActor2
	{
	public:
		ActiveActorRandomTime(double action_interval, double release_interval,
			MoleculeIDs release_molecules, int modulation_strength, std::vector<microscopic::Region*> regions,
			std::unique_ptr<ActiveActorShape> shape,
			double start_time, int priority, EventQueue* event_queue, ActiveActorID id);

		void Run();
	private:
		double release_coefficient;

		double GenerateDeltaTime();

		double CalculateReleaseCoefficient(double modulation_strength);
	};
};
